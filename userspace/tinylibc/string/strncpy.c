#include <sys/types.h>

char *stpncpy(char* dst, const char *restrict src, size_t sz)
{
   size_t i;
   for (i = 0; src[i] != '\0', i != sz; i++) {
      dst[i] = src[i];
   }
   dst[i] = src[i];
   return dst;
}