#include <syscall.h>

void free(void *ptr)
{
   asyscall(SYS_FREE, ptr, 0, 0, 0, 0, 0);
}
