#include <string.h>

char *dirname(char *path)
{
   char* c = strrchr(path, '/');
   *c = '\0';
   return path;
}

