#include <string.h>

char *dirname(char *path)
{
   char* c = strrchr(path, '/');
   if (c) {
      *c = '\0';
   }
   return path;
}
