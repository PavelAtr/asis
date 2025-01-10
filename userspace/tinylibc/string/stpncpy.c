#include <string.h>
#include <strings.h>

char * stpncpy(char* dst, const char* src, size_t sz)
{
   bzero(dst, sz);
   return mempcpy(dst, src, strnlen(src, sz));
}
