#include <sys/stat.h>

/* NOT REALIZED */

int utimensat(int dirfd, const char *pathname,
                     const struct timespec times[], int flags)
{
    return 0;
}

int futimens(int fd, const struct timespec times[])
{
  return 0;
}