#include "httpResponder.h"
#include <cstring>

/*
    Initial responder with Parser that has COMPLETED parse and root path of server. 
 */
HttpResponder::HttpResponder(HttpParser *_hp, const char *_rootPath) : hp(_hp), fileBuf(nullptr), fileLen(0), paddingCheckIdx(0) {
    statusHeadBuf = new char[RESPONDER_BUF_SIZE]; /* TODO: MEMORY POOL? */
    memset(statusHeadBuf, '\0', RESPONDER_BUF_SIZE);

    memset(filePath, '\0', MAX_FILE_PATH_SIZE);

    memset(rootPath, '\0', MAX_ROOT_PATH_SIZE);
    if (strlen(_rootPath) > MAX_ROOT_PATH_SIZE) {
        printf("root path cannot be above %d\n", MAX_ROOT_PATH_SIZE);
        _rootPath = (char*) "/var/www";
    }
    strcpy(rootPath, _rootPath);
}

HttpResponder::~HttpResponder() {
    munmap(fileBuf, fileLen);
    fileBuf = nullptr;
    delete [] statusHeadBuf;
}

/*
    For reusing the responder. 
 */
void HttpResponder::init(HttpParser *newHp, const char *newRootPath) {
    memset(statusHeadBuf, '\0', paddingCheckIdx);
    paddingCheckIdx = 0;
    if (!fileBuf) {
        munmap(fileBuf, fileLen);
        fileBuf = nullptr;
    }
    fileLen = 0;
    memset(filePath, '\0', MAX_FILE_PATH_SIZE);
    memset(rootPath, '\0', MAX_ROOT_PATH_SIZE);

    hp = newHp;
    if (strlen(newRootPath) > MAX_ROOT_PATH_SIZE) {
        printf("root path cannot be above %d\n", MAX_ROOT_PATH_SIZE);
        newRootPath = (char*) "/var/www";
    }
    strcpy(rootPath, newRootPath);
}

HttpResponder::ReturnCode HttpResponder::paddingBackspace() {
    return paddingString((char*) " ");
}

HttpResponder::ReturnCode HttpResponder::paddingEnter() {
    return paddingString((char*) "\n");
}

/*
    Padding status and head buffer with string while update the padding index.
 */
HttpResponder::ReturnCode HttpResponder::paddingString(const char *string) {
    int strLen = strlen(string);
    if(strLen + paddingCheckIdx + 1 > RESPONDER_BUF_SIZE) {
        return RESPONDER_OVER_FLOW;
    }
    strcpy(statusHeadBuf + paddingCheckIdx, string);
    paddingCheckIdx += strlen(string);
    return RESPONDER_OK;
}

/*
    Always examine buffer after padding waste time so just do it at the end.
    If encounter unsupported status return RESPONDER_UNSUPPORT, the CALLER is responsible to deal.
    Only support GET and have no idea what the para after ? means.
 */
HttpResponder::ReturnCode HttpResponder::paddingStatus() {
    static const char *version = "HTTP/1.1";
    
    /* TODO: Support more status */
    StatusCodeDescreptor Status[] = {{(char*) "200", (char*) "OK"},
                                     {(char*) "404", (char*) "NOT FOUND"}};

    if (paddingCheckIdx != 0) {
        return RESPONDER_INIT_ERROR;
    }

    paddingString(version);
    paddingBackspace();

    if (hp->method == HttpParser::METHOD_GET) {
        strcat(filePath, rootPath);
        char *urlSplit;
        
        /* TODO: How to use the para after ?, I dont known! */

        if ((urlSplit = strchr(hp->URL, '?'))) {  
            strncat(filePath, hp->URL, urlSplit - hp->URL);
        }
        else {
            strcat(filePath, hp->URL);
        }

        if (strcmp(hp->URL, "/") == 0) {
            strcat(filePath, (char*) "index.html");
        }

        int s;
        if(access(filePath, F_OK|R_OK) == 0) {
            s = 0;
        }                                           /* TODO: Maybe there are other situations */
        else {
            s = 1;
        }
        paddingString(Status[s].code);
        paddingBackspace();
        paddingString(Status[s].descriptor);
    } 
    else {
        return RESPONDER_UNSUPPORT;
        /* TODO: Support more methods */
    }

    paddingEnter();
    if (paddingCheckIdx + 1 > RESPONDER_BUF_SIZE) {
        return RESPONDER_OVER_FLOW;
    }
    return RESPONDER_OK;
}

/*
    Similar with paddingStatus(). 
 */
HttpResponder::ReturnCode HttpResponder::paddingHead(const char *item) {
    if (strcmp(item, (char*) "Connection") == 0) {
        if (hp->connection == HttpParser::CONNECTION_KEEP_ALIVE) {
            paddingString((char*) "Connection: keep-alive");
        }
        else {
            paddingString((char*) "Connection: close");
            /* TODO: Support more connection type */
        }
    }
    else if (strcmp(item, (char*) "Content-Length") == 0) {
        FILE *objFile;
        if ((objFile = fopen(filePath, "rb"))) {
            fseek(objFile, 0, SEEK_END);
            fileLen = ftell(objFile);
            paddingString((char*) "Content-Length: ");
            if (paddingCheckIdx + (int)log10(fileLen)  <  RESPONDER_BUF_SIZE) {
                sprintf(statusHeadBuf + paddingCheckIdx, "%ld", fileLen);
            }
            else {
                return RESPONDER_OVER_FLOW;
            }
            paddingCheckIdx += (int)log10(fileLen) + 1;        
            fseek(objFile, 0, SEEK_SET);;
            fclose(objFile);
        }
        else {
            paddingString((char*) "Content-Length: 0");
        }
    }
    else {
        return RESPONDER_UNSUPPORT;
        /* TODO: Support more header type */
    }
    paddingEnter();
    if (paddingCheckIdx + 1 > RESPONDER_BUF_SIZE) {
        return RESPONDER_OVER_FLOW;
    }
    return RESPONDER_OK;
}

/*
    Mmap the file to memory and fileBuf points to it. 
    If fail to open or mmap file, assign nullptr to fileBuf.
 */
HttpResponder::ReturnCode HttpResponder::paddingBody() {
    int fd;
    if ((fd = open(filePath, O_RDONLY)) > 0) {
        if ((fileBuf = (char*) mmap(nullptr, fileLen, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0))) {
            close(fd);
            return RESPONDER_OK;
        }
        else {
            close(fd);
            fileBuf = nullptr;
            return RESPONDER_FILE_ERROR;
        }
    }
    else {
        if (access(filePath, F_OK|R_OK) == 0) {
            return RESPONDER_FILE_ERROR;
        }
        else {
            return RESPONDER_OK;
        }
    }
}

/*
    Padding the status and head at statusHeadBuf as well as the body at fileBuf. 
 */
HttpResponder::ReturnCode HttpResponder::padding() {
    ReturnCode rc;
    rc = paddingStatus();
    if (rc != RESPONDER_OK) {
        return rc;
    }
    rc = paddingHead((char*) "Content-Length");
    if (rc != RESPONDER_OK) {
        return rc;
    }
    rc = paddingHead((char*) "Connection");
    if (rc != RESPONDER_OK) {
        return rc;
    }
    rc = paddingEnter();
    if (rc != RESPONDER_OK) {
        return rc;
    }
    rc = paddingBody();
    if (rc != RESPONDER_OK) {
        return rc;
    }
    return RESPONDER_OK;
}

