#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <tiny.h>

char* fullpath(const char* dir, const char* path)
{
   if (path[0] == '/') {
      char* ret = malloc(strlen(path) + 1);
      strcpy(ret, path);
      return ret;
   }
   size_t cwdlen = strlen(dir);
   char* ret = malloc(cwdlen + strlen(path) + 2);
   strcpy(ret, dir);
   strcpy(ret + cwdlen, "/");
   strcpy(ret + cwdlen + 1, path);
   return ret;
}
