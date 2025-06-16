#include <pthread.h>
#include <unistd.h>

#define ONCE_RUNNING 1
#define ONCE_ENDED 2

int pthread_once(pthread_once_t *once_control, void (*init_routine)(void))
{
    while(*once_control) {
        switchtask;
        if (*once_control == ONCE_ENDED) {
            break;
        }
    }
    if (!*once_control) {
        *once_control = ONCE_RUNNING;
        init_routine();
        *once_control = ONCE_ENDED;
    }
    return 0;
}