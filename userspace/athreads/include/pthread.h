#ifndef _PTHREAD_H
#define _PTHREAD_H

#include <sys/types.h>
#include <time.h>

typedef volatile unsigned char pthread_mutex_t;
typedef int pthread_mutexattr_t;

int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

#define PTHREAD_MUTEX_INITIALIZER 0

typedef unsigned int pthread_attr_t;

typedef struct {
    pid_t pid; // Process ID
    pthread_attr_t attr; // Thread attributes
    int state; // Thread state (e.g., running, waiting)
    void* ret;
} pthread_t;

#define THREAD_TERMINATED 0x01

int pthread_create(pthread_t* thread,
         const pthread_attr_t* attr,
         void *(*start_routine)(void *),
         void *restrict arg);

int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);

typedef int pthread_condattr_t;
typedef struct {
    pthread_condattr_t dummy; // Placeholder for condition variable attributes
}
pthread_cond_t;
#define PTHREAD_COND_INITIALIZER {0}

int pthread_cond_init(pthread_cond_t *cond, pthread_condattr_t *cond_attr);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex,
    const struct timespec *abstime);
int pthread_cond_destroy(pthread_cond_t *cond);

int apthread_join(pthread_t* thread, void **retval);
#define pthread_join(t, r) apthread_join(&t, r)


#endif
