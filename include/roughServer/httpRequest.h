#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "request.h"
#include "httpParser.h"
#include "httpResponder.h"
#include <sys/epoll.h>
#include "setEpoll.h"

#define HTTP_REQUEST_BUFFER_SIZE 1024

class HttpRequest {
public:
    enum HttpRequestStatus {HTTP_REQUEST_CLOSE = 0, HTTP_REQUEST_READ, HTTP_REQUEST_PROCESS, HTTP_REQUEST_WRITE};
    enum ReadStatus {READ_OK = 0, READ_AGAIN, READ_OVER_FLOW, READ_ERROR};
    enum WriteStatus {WRITE_OK = 0, WRITE_AGAIN, WRITE_OVER_FLOW, WRITE_ERROR};
private:
    int sockFd;
    int epollFd;
    char clientIP[12];
    int clientPort;
    char *readBuf;
    int readBufLen;
    int readBufIdx;
    int writeBufIdx;
    char rootPath[MAX_ROOT_PATH_SIZE];
    HttpParser *hp;
    HttpResponder *hr;
    HttpRequestStatus requestStatus;
public:
    HttpRequest(int _sockFd = 0, int _epollFd = 0, char *_rootPath = (char*) "/var/www");
    ~HttpRequest();
    ReadStatus read();
    WriteStatus write();
    void closeConnection();
    void init(int _sockFd, int _epollFd, char *_rootPath = (char*) "var/www");
 /* TODO: If allocate HttpRequst staticly it is not neccessary to change sock, epoll and rootPath. */
    void init(); 
    void process();
};


#endif //HTTPREQUEST_H
