#include <string.h>

void *rawmemchr(const void* s, int c)
{
   return memchr(s, c, strlen(s));
}