#include <string.h>
char* origin = "libac.so"; /* GARBAGE */

char* basename(char* path)
{
   char* ret = strrchr(path, '/');
   if (ret) {
      return ret  + sizeof(char);
   } else {
      return path;
   }
}
