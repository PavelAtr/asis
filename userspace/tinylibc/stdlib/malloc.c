#include <stdlib.h>
#include <syscall.h>

void* malloc(size_t size)
{
    return (void*)syscall(SYS_MALLOC, size);
}
