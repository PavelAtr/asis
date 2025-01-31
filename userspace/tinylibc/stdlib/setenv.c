#include <string.h>
#include <stdlib.h>
#include <errno.h>

extern char*** environ;

int envid(const char *name);
int envnewid();

int setenv(const char *name, const char *value, int overwrite)
{
   int i = envid(name);
   if (i == -1) {
      i = envnewid();
      if (i == -1) {
         errno = ENOMEM;
         return -1;
      }
   } else {
      free((*environ)[i]);
   }
   (*environ)[i] = malloc(strlen(name) + strlen(value) + 2);
   strcpy((*environ)[i], name);
   strcat((*environ)[i], "=");
   strcat((*environ)[i], value);
   return 0;
}

