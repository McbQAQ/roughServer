#ifndef HTTPRESPONDER_H
#define HTTPRESPONDER_H

#include "httpParser.h"
#include <sys/uio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <sys/mman.h>


#define RESPONDER_BUF_SIZE 1024
#define MAX_ROOT_PATH_SIZE 32
#define MAX_FILE_PATH_SIZE 64

class HttpResponder {
    friend class HttpRequest;    
public:
    enum ReturnCode {RESPONDER_OK = 0, RESPONDER_OVER_FLOW, RESPONDER_INIT_ERROR, RESPONDER_FILE_ERROR, RESPONDER_UNSUPPORT};
    struct StatusCodeDescreptor {
        const char *code;
        const char *descriptor;
    };
private:
    HttpParser *hp;
    char rootPath[MAX_ROOT_PATH_SIZE];
private:
    char *statusHeadBuf; 
    char filePath[MAX_FILE_PATH_SIZE];
    char *fileBuf;
    long fileLen;
    int paddingCheckIdx;
    
    ReturnCode paddingString(const char*);
    ReturnCode paddingBackspace();
    ReturnCode paddingEnter();
private:
    ReturnCode paddingStatus();
    ReturnCode paddingHead(const char *item);
    ReturnCode paddingBody();
public:
    HttpResponder(HttpParser *_hp, const char *_rootPath = (char*) "/var/www");
    ~HttpResponder();
    void init(HttpParser *newHp, const char *newRootPath = (char*) "/var/www");
    ReturnCode padding();
};

#endif
