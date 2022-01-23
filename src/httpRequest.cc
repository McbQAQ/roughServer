#include "httpRequest.h"
#include "setEpoll.h"
#include <cstddef>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <sys/uio.h>

HttpRequest::HttpRequest(int _sockFd, int _epollFd, char *_rootPath) : sockFd(_sockFd), epollFd(_epollFd), readBuf(nullptr), hp(nullptr), hr(nullptr) {
    if (strlen(_rootPath) > MAX_ROOT_PATH_SIZE) {
        printf("size of root path cannot be above %d\n", MAX_ROOT_PATH_SIZE);
        _rootPath = (char*) "/var/www";
    }
    strcpy(rootPath, _rootPath);
    requestStatus = HTTP_REQUEST_CLOSE;

}

HttpRequest::~HttpRequest() {
    if (readBuf) {
        delete [] readBuf;
    }
    if (hp) {
        delete hp;
    }
    if (hr) {
        delete hr;
    }
    
}

/*
    read recv data from client to read buffer. 
 */
HttpRequest::ReadStatus HttpRequest::read() {
    int len;
    while(1) {
        len = recv(sockFd, readBuf + readBufIdx, HTTP_REQUEST_BUFFER_SIZE - readBufIdx, 0);
        if (len == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return READ_OK;
            }
            return READ_ERROR;
        }
        else if (len == 0) {
            return READ_ERROR;
        }

        readBufIdx += len;
    }
    if (readBufIdx > HTTP_REQUEST_BUFFER_SIZE) {
        return READ_OVER_FLOW;
    }
    return READ_OK;
}

HttpRequest::WriteStatus HttpRequest::write() {
    while(1) {
        iovec sendData[2];
        int ivCnt = 0;
        if (writeBufIdx < hr->paddingCheckIdx) {
            sendData[0].iov_base = hr->statusHeadBuf + writeBufIdx;
            sendData[0].iov_len = hr->paddingCheckIdx - writeBufIdx;
            if (!hr->fileBuf) {
                ivCnt = 1;
            }
            else {
                sendData[1].iov_base = hr->fileBuf;
                sendData[1].iov_len = hr->fileLen;
                ivCnt = 2;
            }
        }
        else if (writeBufIdx >= hr->paddingCheckIdx && writeBufIdx < (hr->paddingCheckIdx+hr->fileLen)) {
            sendData[0].iov_base = hr->fileBuf + (writeBufIdx - hr->paddingCheckIdx);
            sendData[0].iov_len = hr->fileLen - (writeBufIdx - hr->paddingCheckIdx);
            ivCnt = 1;
        }
        
        int ret;
        if ((ret = writev(sockFd, sendData, ivCnt)) <= -1) {
            if (errno == EAGAIN) {
                return WRITE_AGAIN;
            }
            return WRITE_ERROR;
        }
        writeBufIdx += ret;
        if (writeBufIdx >= (sendData[0].iov_len + sendData[1].iov_len)) {
            return WRITE_OK;
        }
    }
}

/*
    Close connection while reserve memory of HttpRequest for next connection.
    Call init() before next connection.
 */
void HttpRequest::closeConnection() {
    removeFd(epollFd, sockFd);
    memset(clientIP, '\0', strlen(clientIP));
    clientPort = 0;
    delete [] readBuf;
    readBuf = nullptr;
    readBufLen = 0;
    readBufIdx = 0;
    writeBufIdx = 0;
    delete hp;
    delete hr;
    hp = nullptr;
    hr = nullptr;
    requestStatus = HTTP_REQUEST_CLOSE;
    close(sockFd);
}

/*
    No usage currently. 
 */
void HttpRequest::init(int _sockFd, int _epollFd, char *_rootPath) {
    sockFd = _sockFd;
    epollFd = _epollFd;

    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    getpeername(sockFd, (sockaddr*) &clientAddr, &clientAddrLen);
    strcpy(clientIP, inet_ntoa(clientAddr.sin_addr));
    clientPort = ntohs(clientAddr.sin_port);

    if (!readBuf) {
        readBuf = new char[HTTP_REQUEST_BUFFER_SIZE];
    }
    memset(readBuf, '\0', HTTP_REQUEST_BUFFER_SIZE);
    readBufLen = HTTP_REQUEST_BUFFER_SIZE;
    readBufIdx = 0;

    if (strlen(_rootPath) > MAX_ROOT_PATH_SIZE) {
        printf("size of root path cannot be above %d\n", MAX_ROOT_PATH_SIZE);
        _rootPath = (char*) "/var/www";
    }
    strcpy(rootPath, _rootPath);

    if(!hp) {
        hp = new HttpParser(readBuf, readBufLen);
    }
    else {
        hp->init(readBuf, 0, HTTP_REQUEST_BUFFER_SIZE);
    }

    if (!hr) {
        hr = new HttpResponder(hp, rootPath);
    }
    else {
        hr->init(hp, _rootPath);
    }
    requestStatus = HTTP_REQUEST_READ;

}

/*
    Init for reuse. 
 */
void HttpRequest::init() {
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    getpeername(sockFd, (sockaddr*) &clientAddr, &clientAddrLen);
    memset(clientIP, '\0', strlen(clientIP));
    strcpy(clientIP, inet_ntoa(clientAddr.sin_addr));
    clientPort = ntohs(clientAddr.sin_port);

    if (!readBuf) {
        readBuf = new char[HTTP_REQUEST_BUFFER_SIZE];
    }
    memset(readBuf, '\0', HTTP_REQUEST_BUFFER_SIZE);
    readBufLen = HTTP_REQUEST_BUFFER_SIZE;
    readBufIdx = 0;

    writeBufIdx = 0;

    if(!hp) {
        hp = new HttpParser(readBuf, readBufLen);
    }
    else {
        hp->init(readBuf, 0, HTTP_REQUEST_BUFFER_SIZE);
    }

    if (!hr) {
        hr = new HttpResponder(hp, rootPath);
    }
    else {
        hr->init(hp, rootPath);
    }
    requestStatus = HTTP_REQUEST_READ;
}

void HttpRequest::process() {
    if (requestStatus == HTTP_REQUEST_CLOSE) {
        init();
        requestStatus = HTTP_REQUEST_READ;
    }

    if (requestStatus == HTTP_REQUEST_READ) {
        ReadStatus readRet = read();

        if (readRet == READ_OK) {
            HttpParser::LineParserStatus parseRet = hp->parse();
            if (parseRet == HttpParser::LINE_OK) {
                requestStatus = HTTP_REQUEST_PROCESS;
            }
            else if (parseRet == HttpParser::LINE_INCOMPLETE) {
                resetOneShot(epollFd, sockFd, EPOLLIN|EPOLLET|EPOLLONESHOT|EPOLLRDHUP);
                return;
            }
            else {
                printf("the data receive has broken, close connection\n");
                closeConnection();
                return;
            }
        }
        else if (readRet == READ_AGAIN) {
            resetOneShot(epollFd, sockFd, EPOLLIN|EPOLLET|EPOLLONESHOT|EPOLLRDHUP);
            return;
        }
        else {
            printf("error occur in reading from socket, close connection\n");
            closeConnection();
            return;
        }
    }
    
    if (requestStatus == HTTP_REQUEST_PROCESS) {
        HttpResponder::ReturnCode responderRet = hr->padding();
        if (responderRet == HttpResponder::RESPONDER_OK) {
            requestStatus = HTTP_REQUEST_WRITE;
        }
        else {
            printf("error %d occur in padding, close connection\n", responderRet);
            closeConnection();
            return;
        }
    }

    if (requestStatus == HTTP_REQUEST_WRITE) {
        WriteStatus writeRet = write();
        if (writeRet == WRITE_OK) {
            if (hp->connection == HttpParser::CONNECTION_KEEP_ALIVE) {
                requestStatus = HTTP_REQUEST_CLOSE;
                resetOneShot(epollFd, sockFd, EPOLLIN|EPOLLET|EPOLLONESHOT|EPOLLRDHUP);
                return;
            }
            else {
                closeConnection();
                return;
            }
        }
        else if (writeRet == WRITE_AGAIN) {
            resetOneShot(epollFd, sockFd, EPOLLOUT|EPOLLET|EPOLLONESHOT|EPOLLRDHUP);
            return;
        }
        else {
            printf("error %d occur in writing, close connection\n", writeRet);
            closeConnection();
            return;
        }
    }
}
