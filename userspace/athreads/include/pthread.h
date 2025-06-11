#ifndef _PTHREAD_H
#define _PTHREAD_H

typedef volatile unsigned char pthread_mutex_t;
typedef int pthread_mutexattr_t;

int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

#define PTHREAD_MUTEX_INITIALIZER 0
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#endif
