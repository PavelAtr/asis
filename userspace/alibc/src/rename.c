#include <syscall.h>

int rename(const char *oldpath, const char *newpath)
{
   return syscall(SYS_RENAME, oldpath, newpath);
}
