#include <time.h>
#include <unistd.h>


int clock_nanosleep(clockid_t clockid, int flags,
                           const struct timespec *request,
                           struct timespec * remain)
{
    switchtask;
    return 0;
}