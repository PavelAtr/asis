#include <syscall.h>

int link(const char *oldpath, const char *newpath)
{
   return (int)asyscall(SYS_LINK, oldpath, newpath, 0, 0, 0, 0);
}