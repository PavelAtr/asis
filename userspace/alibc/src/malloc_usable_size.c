#include <sys/malloc.h>
#include <syscall.h>

size_t malloc_usable_size(void *ptr)
{
    return (size_t) asyscall(SYS_MALLOCUSABLE, ptr, 0, 0, 0, 0, 0);
}
