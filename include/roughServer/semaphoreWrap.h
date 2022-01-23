#ifndef SEMAPHOREWRAP_H
#define SEMAPHOREWRAP_H

#include <semaphore.h>

class Semaphore {
private:
    sem_t sem;
public:
    Semaphore(int value = 0) {
        sem_init(&sem, 0, value);
    }

    int post() {
        return sem_post(&sem); 
    }

    int wait() {
        return sem_wait(&sem);
    }

    ~Semaphore() {
        sem_destroy(&sem);
    }
};

#endif
