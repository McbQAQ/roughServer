#include "httpParser.h"

HttpParser::HttpParser(char *_readBuf, int _readBufLen) : readBuf(_readBuf), readBufLen(_readBufLen) {
    checkIdx = 0;
    checkStatus = PARSER_REQUEST;
    method = METHOD_OTHERS;
    URL = version = host = body = nullptr;
    connection = CONNECTION_OTHERS;
    contentLenth = 0;
}

HttpParser::~HttpParser() {

}

/*
    Parse the request line.
    Ensure the checkIdx point to the FIRST chractor of the request line.
    Return LINE_OK and move the checkIdx to the FIRST charactor of the NEXT line if line is OK.
    Return LINE_INCOMPLETE and remain checkIdx UNCHANGED if line is INCOMPLETE.
    Return LINE_BROKEN and remain checkIdx UNCHANGED if line is WRONG. 
*/
HttpParser::LineParserStatus HttpParser::parseRequestLine() {
    if (checkIdx != 0) {
        return LINE_BROKEN;
    }
    if (!strchr(readBuf + checkIdx, '\n')) {
        return LINE_INCOMPLETE;
    }
    int spaceIdx = 0;
    int idx = 0;
    int endFlag = 0;
    while((spaceIdx = strcspn(readBuf + checkIdx, (char*) " \n")) && !endFlag) {
        if (*(readBuf + checkIdx + spaceIdx) == '\n') {
            endFlag = 1;
        }
        *(readBuf + checkIdx + spaceIdx) = '\0';
        switch (idx) {
            case 0: 
                if (strcmp(readBuf + checkIdx, (char*) "GET") == 0) {
                    method = METHOD_GET;
                }
                else {
                    method = METHOD_OTHERS;
                    /* TODO: support more method */
                }
                break;
            case 1:
                URL = readBuf + checkIdx;
                break;
            case 2:
                version = readBuf + checkIdx;
                break;
            default:
                return LINE_BROKEN;
        }
        idx++;
        checkIdx = checkIdx + spaceIdx + 1;
    }
    return LINE_OK;  
}

/*
    Similar with parseRequestLine(). 
 */
HttpParser::LineParserStatus HttpParser::parseHeadLine() {
    char *end;
    if (!(end = strchr(readBuf + checkIdx, '\n'))) {
        return LINE_INCOMPLETE;
    }
    *end = '\0';
    if (end == (readBuf + checkIdx + 1)) {
        checkIdx++;
        return LINE_EMPTY;
    }

    int colonIdx = strcspn(readBuf + checkIdx, ":");
    *(readBuf + checkIdx + colonIdx) = '\0';
    *(readBuf + checkIdx + colonIdx + 1) = '\0';
    if (strcmp(readBuf + checkIdx, "Host") == 0) {
        host = readBuf + checkIdx + colonIdx + 2;
    }
    else if (strcmp(readBuf + checkIdx, "Connection") == 0) {
        /*************************************************/
        int flag = 1;
        char *c = readBuf + checkIdx + colonIdx + 2;
        char *s = (char*) "keep-alive";
        while(*c && *s) {
            if (*c != *s) {
                flag = 0;
                break;
            }
            ++c;
            ++s;
        }
        /*************************************************/
        if (strcmp(readBuf + checkIdx + colonIdx + 2, "keep-alive\0") == 0 || flag) {
            connection = CONNECTION_KEEP_ALIVE;
        }
        else {
            connection = CONNECTION_OTHERS;
            /* TODO: support more connection type */
        }
    }
    else if (strcmp(readBuf + checkIdx, "Content-Length") == 0) {
        contentLenth = atoi(readBuf + checkIdx + colonIdx + 2);
    }
    else {
        /* TODO: Process more head */
    }

    checkIdx = (int)(end - readBuf) + 1;
    return LINE_OK;
}

/*
    Parse the body.
    Remain checkIdx unchanged whatever.
    Compare length of body in buffer with CONTENT-LENGTH head item.
 */
HttpParser::LineParserStatus HttpParser::parseBodyLine() {
   int bodyLen = strlen(readBuf + checkIdx);
   if (bodyLen < contentLenth) {
       return LINE_INCOMPLETE;
   }
   else if (bodyLen > contentLenth) {
       return LINE_BROKEN;
   }
   else {
       body = readBuf + checkIdx;
       return LINE_OK;
   }
}

/*
    Parse the http message located at readBuf by finite status machine. 
 */
HttpParser::LineParserStatus HttpParser::parse() {
    while(1) {
        LineParserStatus status;
        switch (checkStatus) {
            case PARSER_REQUEST:
                status = parseRequestLine();
                if (status == LINE_OK) {
                    checkStatus = PARSER_HEADER;
                }
                else {
                    return status;
                }
                break;
            case PARSER_HEADER:
                status = parseHeadLine();
                if (status == LINE_EMPTY) {
                    checkStatus = PARSER_BODY;
                }
                else if (status != LINE_OK) {
                    return status;
                }
                break;
            case PARSER_BODY:
                status = parseBodyLine();
                return status;
                break;
            default:
                return LINE_BROKEN;
        }
    }
}

/*
    Initial the parser when reuse.
 */
void HttpParser::init(char *newReadBuf, int newCheckIdx, int newReadBufLen) {
    readBuf = newReadBuf;
    checkIdx = 0;
    readBufLen = newReadBufLen;
    checkStatus = PARSER_REQUEST;
    method = METHOD_OTHERS;
    URL = version = host = body = nullptr;
    connection = CONNECTION_OTHERS;
    contentLenth = 0; 
}

char *HttpParser::getURL() const {
    return URL;
}

HttpParser::ConnectionType HttpParser::getConnType() const {
    return connection;
}
