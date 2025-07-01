#include <syscall.h>
#include <sys/types.h>
#include <stdlib.h>

void *realloc(void *ptr, size_t size)
{

   return asyscall(SYS_REALLOC, ptr, size, 0, 0, 0, 0);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
   return realloc(ptr, nmemb * size);
}

