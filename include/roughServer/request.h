#ifndef REQUEST_H
#define REQUEST_H

#include <unistd.h>
#include <stdio.h>

class RequestInterface {
private:
public:
    virtual int read();
    virtual int write();
    virtual int closeConnection();
    virtual void process() = 0;
};

#endif
