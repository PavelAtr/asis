#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int sem_init(sem_t *sem, int pshared, unsigned int value)
{
    sem->value = value;
    sem->fd = -1;
    return 0;
}

int sem_destroy(sem_t *sem)
{
    return 0;
}

int sem_wait(sem_t *sem)
{
    if (sem->value)
        sem->value--;
    while (!sem->value) switchtask;
    return 0;
}
int sem_trywait(sem_t *sem)
{
    if (sem->value)
        sem->value--;
    if (!sem->value) {
	errno = EAGAIN;
	return -1;
    }
}

int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout)
{
    /* TIMES NOT REALIZED */
    return sem_trywait(sem);
}

int sem_post(sem_t *sem)
{
    sem->value++;
    return 0;
}

sem_t *sem_open(const char *name, int oflag)
{
/* NOT REALIZED */
    return NULL;
}

int sem_close(sem_t *sem)
{
/* NOT REALIZED */
    return 0;
}

