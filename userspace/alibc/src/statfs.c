#include <sys/statfs.h>

/* NOT REALIZED */

int statfs(const char *path, struct statfs *buf)
{
   return 0;
}

int fstatfs(int fd, struct statfs *buf)
{
   return 0;
}