#include <pthread.h>
#include <unistd.h>

int pthread_mutex_lock(pthread_mutex_t *mutex)
{
    while(*mutex) switchtask;
    *mutex = 1;
    return 0;
}

int pthread_mutex_timedlock(pthread_mutex_t * mutex,
    const struct timespec * abs_timeout)
{
/* NOT REALIZED FULLY */
  if (*mutex == 0) {
	*mutex = 1;
	return 0;
   }
   return -1;
}

int pthread_mutex_trylock(pthread_mutex_t *mutex)
{
   if (*mutex == 0) {
	*mutex = 1;
	return 0;
   }
   return -1;
}

int pthread_mutex_unlock(pthread_mutex_t *mutex)
{
    *mutex = 0;
    return 0;
}

int pthread_mutex_init(pthread_mutex_t* mutex,
    const pthread_mutexattr_t* attr)
{
    *mutex = 0;
    return 0;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
    return 0;
}

int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type)
{
    return 0;
}

