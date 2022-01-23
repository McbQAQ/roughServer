#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <pthread.h>
#include "semaphoreWrap.h"
#include "mutexWrap.h"
#include "httpRequest.h"
#include <list>

class ThreadPool {
private:
    pthread_t *pool;
    int threadNum;
    int maxRequest;
    std::list<HttpRequest*> requestQueue;
    Mutex mlock;
    Semaphore sema;
    int stopFlag;
    void _worker();
    static void *worker(void*);
public:
    ThreadPool(int _threadNum = 6, int _maxRequest = 12);
    int add(HttpRequest*);
    ~ThreadPool();
};

#endif
