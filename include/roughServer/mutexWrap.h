#ifndef MUTEXWRAP_H
#define MUTEXWRAP_H

#include <pthread.h>

class Mutex {
private:
    pthread_mutex_t mlock;
public:
    Mutex() {
        pthread_mutex_init(&mlock, nullptr);
    }

    int lock() {
        return pthread_mutex_lock(&mlock);
    }

    int unlock() {
        return pthread_mutex_unlock(&mlock);
    }

    ~Mutex() {
        pthread_mutex_destroy(&mlock);
    }
    
};


#endif
