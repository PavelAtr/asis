#include <unistd.h>
#include <syscall.h>
#include <stddef.h>
#include <time.h>

/* BAD REALIZED */

int nanosleep(const struct timespec *req, struct timespec* rem)
{
   rem = NULL;
   (int)asyscall(SYS_USLEEP, req->tv_sec * 1000000000 + req->tv_nsec, 0, 0, 0, 0, 0);
   return 0;
}
