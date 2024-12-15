#include <syscall.h>
#include <sys/types.h>

void *realloc(void *ptr, size_t size)
{
   return (void*)syscall(SYS_REALLOC, ptr, size);
}
