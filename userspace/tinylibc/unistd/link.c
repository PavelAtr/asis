#include <syscall.h>

int link(const char *oldpath, const char *newpath)
{
  return syscall(SYS_LINK, oldpath, newpath);
}