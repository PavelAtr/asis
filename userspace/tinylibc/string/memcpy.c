#include <sys/types.h>

void* memcpy(void* dest, const void* src, size_t n)
{
    size_t i;
    for (i = 0; i < n; i++)
	((char*)dest)[i] = ((char*)src)[i];
    return dest;
}
