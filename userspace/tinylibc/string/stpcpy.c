#include <string.h>

char *stpcpy(char* dst, const char* src)
{
   char* ret = strcpy(dst, src);
   return ret + strlen(ret);
}