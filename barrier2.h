#ifndef BARRIER2_H
#define BARRIER2_H

#include <pthread.h>

class Barrier {
public:
    Barrier(int count);
    ~Barrier();
    int wait();   

private:
    int nthread_total;
    int nthread_arrived;
    int iter;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

#endif  
