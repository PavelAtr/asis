#include <string.h>

char *strchr(const char *s, int c)
{
   size_t len;
   for (len = 0; s[len] != '\0'; len ++)
      if (s[len] == c) {
         return (char*)&s[len];
      }
   return NULL;
}
