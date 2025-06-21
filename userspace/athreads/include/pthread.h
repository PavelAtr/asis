#ifndef _PTHREAD_H
#define _PTHREAD_H

#include <sys/types.h>
#include <time.h>

typedef volatile unsigned char pthread_mutex_t;
typedef int pthread_mutexattr_t;
#define PTHREAD_MUTEX_RECURSIVE 1

int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
int pthread_mutex_timedlock(pthread_mutex_t * mutex,  const struct timespec * abs_timeout);

#define PTHREAD_MUTEX_INITIALIZER 0

typedef unsigned int pthread_attr_t;
#define PTHREAD_KEYS_MAX 32
typedef int pthread_key_t;

typedef struct {
    void* data;
    void (*destructors)(void*);
} tsdata;

typedef struct {
    pid_t pid; // Process ID
    pthread_attr_t attr; // Thread attributes
    int state; // Thread state (e.g., running, waiting)
    void* ret;
    tsdata* tsd[PTHREAD_KEYS_MAX]; // Thread-specific data (TSD) для pthread_key_t
} pthread_t;

#define THREAD_TERMINATED 0x01

int pthread_create(pthread_t* thread,
         const pthread_attr_t* attr,
         void *(*start_routine)(void *),
         void *arg);

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

typedef char pthread_once_t;
#define PTHREAD_ONCE_INIT 0;
int pthread_once(pthread_once_t *once_control, void (*init_routine)(void));

pthread_t* pthread_self();

int pthread_key_create(pthread_key_t *key, void (*destructor)(void*));
int pthread_key_delete(pthread_key_t key);
int pthread_setspecific(pthread_key_t key, const void *value);
void* pthread_getspecific(pthread_key_t key);

extern __thread pthread_t* self;
#define pthread_self() *self
int pthread_detach(pthread_t thread);
int pthread_equal(pthread_t t1, pthread_t t2);
void pthread_exit(void *retval);

typedef int pthread_barrier_t;

#endif
