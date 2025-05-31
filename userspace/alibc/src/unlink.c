#include <syscall.h>
#include <stdlib.h>
#include <unistd.h>

int unlink(const char *pathname)
{
   return asyscall(SYS_UNLINK, pathname, 0, 0, 0, 0, 0);
}