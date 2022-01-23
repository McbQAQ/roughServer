#include "threadPool.h"
#include "semaphoreWrap.h"
#include "stdio.h"
#include <sys/time.h>


ThreadPool::ThreadPool(int _threadNum, int _maxRequest) : threadNum(_threadNum), 
    maxRequest(_maxRequest), requestQueue(), mlock(), sema(), stopFlag(0) {
    if (_threadNum < 0) {
        printf("the number of thread must above 0! replace by the default\n");
        threadNum = 6;
    }
    if (_maxRequest < 0) {
        printf("the max number of the request must above 0! replace by default\n");
        maxRequest = 12;
    }
    pool = new pthread_t[threadNum];
    for (int i = 0; i < threadNum; i++) {
        if (pthread_create(pool+i, nullptr, worker, this) != 0) {
            delete pool;
            printf("error occured when create thread\n");
        }
        
        if (pthread_detach(pool[i]) != 0) {
            delete pool;
            printf("error occured when detach thread %d\n", (int)*(pool+i));
        }
    }
}

ThreadPool::~ThreadPool() {
    printf("the thread pool is stopped\n");
    stopFlag = 1;
    delete pool;
}

void ThreadPool::_worker() {
    while(!stopFlag) {
        sema.wait();
        mlock.lock();
        if (requestQueue.empty()) {
            mlock.unlock();
            continue;
        }
        HttpRequest *r = requestQueue.front();
        requestQueue.pop_front();
        mlock.unlock();
        if (!r) {
            continue;
        }
        r->process();
    }
}

void *ThreadPool::worker(void *t) {
    ThreadPool *self = (ThreadPool*) t;
    self->_worker();
    printf("process exit\n");
    return t;
}

int ThreadPool::add(HttpRequest *r) {
    mlock.lock();
    if (requestQueue.size() > maxRequest) { 
        mlock.unlock();
        return 0;
    }
    requestQueue.push_back(r);
    mlock.unlock();
    sema.post();
    return 1;
}
