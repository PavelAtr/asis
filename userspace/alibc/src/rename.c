#include <syscall.h>

int rename(const char *oldpath, const char *newpath)
{
   return (int)asyscall(SYS_RENAME, oldpath, newpath, 0, 0, 0, 0);
}
