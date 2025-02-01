#include <string.h>
#include <stdlib.h>
#include <errno.h>

int envid(const char *name);
int envnewid();

char *getenv(const char *name)
{
   int i = envid(name);
   if (i == -1) {
      return NULL;
   }
   return (char*)&(environ[i])[strlen(name) + 1];
}

