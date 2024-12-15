#include <sys/types.h>

int memcmp(const void* s1, const void* s2, size_t n)
{
   size_t i;
   for (i = 0; i < n; i++) {
      if (((unsigned char*)s1)[i] < ((unsigned char*)s2)[i]) return -1;
      if (((unsigned char*)s1)[i] > ((unsigned char*)s2)[i]) return 1;
   }
   return 0;
}
