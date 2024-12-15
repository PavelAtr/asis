#include <string.h>

char *strrchr(const char *s, int c)
{
   size_t len;
   for (len = strlen(s) - 1; len >=0; len --)
      if (s[len] == c) {
         return (char*)&s[len];
      }
   return NULL;
}