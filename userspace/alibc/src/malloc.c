#include <stdlib.h>
#include <syscall.h>

void* malloc(size_t size)
{
   return asyscall(SYS_MALLOC, size, 0, 0, 0, 0, 0);
}
