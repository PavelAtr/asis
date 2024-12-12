#include <stdlib.h>
#include <string.h>

void *calloc(size_t nmemb, size_t size)
{
   size_t len = nmemb * size;
   void* ret = malloc(len);
   memset(ret, 0x0, len);
   return ret;
}
