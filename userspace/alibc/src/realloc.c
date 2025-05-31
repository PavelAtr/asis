#include <syscall.h>
#include <sys/types.h>

void *realloc(void *ptr, size_t size)
{
   return (void*)asyscall(SYS_REALLOC, ptr, size, 0, 0, 0, 0);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
   return realloc(ptr, nmemb * size);
}

