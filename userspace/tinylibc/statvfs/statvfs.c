#include <sys/statvfs.h>

/* NOT REALIZED */

int statvfs(const char* path, struct statvfs* buf)
{
   return 0;
}

int fstatvfs(int fd, struct statvfs *buf)
{
   return 0;
}