#include <sys/types.h>

void bcopy(const void* src, void* dest, size_t n)
{
   size_t i;
   for (i = 0; i < n; i++) {
      ((char*)dest)[i] = ((char*)src)[i];
   }
}
