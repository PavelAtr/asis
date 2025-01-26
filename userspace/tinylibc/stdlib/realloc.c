#include <syscall.h>
#include <sys/types.h>

void *realloc(void *ptr, size_t size)
{
   return (void*)syscall(SYS_REALLOC, ptr, size);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
   return realloc(ptr, nmemb * size);
}

