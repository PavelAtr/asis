#include <syscall.h>

void free(void *ptr)
{
   syscall(SYS_FREE, ptr);
}
