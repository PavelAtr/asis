#include <string.h>

char* basename(char* path)
{
   char* ret = strrchr(path, '/');
   if (ret) {
      return ret  + sizeof(char);
   } else {
      return path;
   }
}
