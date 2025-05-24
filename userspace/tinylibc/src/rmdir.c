#include <syscall.h>
#include <stdlib.h>
#include <unistd.h>

int rmdir(const char *pathname)
{
   return syscall(SYS_UNLINK, pathname);
}
