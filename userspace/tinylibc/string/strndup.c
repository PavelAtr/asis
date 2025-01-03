#include <string.h>
#include <stdlib.h>

char *strndup(const char* s, size_t n)
{
   char* ret = malloc(n + 1);
   strncpy(ret, s, n);
   ret[n] = '\0';
   return ret;
}