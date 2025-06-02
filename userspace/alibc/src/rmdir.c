#include <syscall.h>
#include <stdlib.h>
#include <unistd.h>

int rmdir(const char *pathname)
{
   return (int)asyscall(SYS_UNLINK, pathname, 0, 0, 0, 0, 0);
}
