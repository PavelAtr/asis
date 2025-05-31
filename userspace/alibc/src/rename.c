#include <syscall.h>

int rename(const char *oldpath, const char *newpath)
{
   return asyscall(SYS_RENAME, oldpath, newpath, 0, 0, 0, 0);
}
