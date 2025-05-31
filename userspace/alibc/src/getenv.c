#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int envid(const char *name);

char *getenv(const char *name)
{
   INIT_ENVIRON
   int i = envid(name);
   if (i == -1) {
      return NULL;
   }
   return (char*)&(environ[i])[strlen(name) + 1];
}

