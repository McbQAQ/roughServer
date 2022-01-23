#ifndef HTTPPARSER_H
#define HTTPPARSER_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class HttpParser {
    friend class HttpRequest;
    friend class HttpResponder;
public:
    enum HttpMethod {METHOD_GET = 0, METHOD_POST, METHOD_PUT, METHOD_DELETE, METHOD_TRACE, METHOD_OPTION, METHOD_HEAD, METHOD_OTHERS};
    enum ConnectionType {CONNECTION_KEEP_ALIVE = 0, CONNECTION_OTHERS};
    enum ParseStatus {PARSER_REQUEST = 0, PARSER_HEADER, PARSER_BODY};
    enum LineParserStatus {LINE_OK = 0, LINE_INCOMPLETE, LINE_BROKEN, LINE_EMPTY};
private:
    char *readBuf;
    int readBufLen;
    int checkIdx;
    ParseStatus checkStatus;
    HttpMethod method;
    char *URL;
    char *version;
    char *host;
    ConnectionType connection;
    long contentLenth;
    char *body;
private:
    LineParserStatus parseRequestLine();
    LineParserStatus parseHeadLine();
    LineParserStatus parseBodyLine();
public:
    HttpParser(char *_readBuf, int _readBufLen);
    ~HttpParser();
    LineParserStatus parse();  /* Finite status machine */
    void init(char *newReadBuf = nullptr, int newCheckIdx = 0, int newReadBufLen = 0);
public:
    char *getURL() const;
    ConnectionType getConnType() const;
};


#endif
