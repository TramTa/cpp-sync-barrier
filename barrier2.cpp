#include "barrier2.h"
#include <iostream>

Barrier::Barrier(int count)
    : nthread_total(count), nthread_arrived(0), iter(0)
{
    if (pthread_mutex_init(&mutex, nullptr) != 0 ||
        pthread_cond_init(&cond, nullptr) != 0) 
    {
        std::cerr << "Error with Mutex or Cond init" << std::endl;
        exit(1);
    }
}


Barrier::~Barrier() 
{
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}


int Barrier::wait()
{
    pthread_mutex_lock(&mutex);
    nthread_arrived++;

    if (nthread_arrived == nthread_total) {
        iter = (iter == 0) ? 1 : 0;
        nthread_arrived = 0;
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    } 
    else {
        int local_iter = iter;
        while (local_iter == iter)
            pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    return 1;
}

