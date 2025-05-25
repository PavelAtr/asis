#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>
#include <errno.h>

char** environ = (char*[]){
    NULL,
};

int envid(const char *name)
{
   INIT_ENVIRON
   if (!environ) {
      return -1;
   }
   int i;
   for(i = 0; environ[i]; i++)
      if (strstr(environ[i], name) == environ[i]
         && (environ[i])[strlen(name)] == '=') {
         return i;
      }
   return -1;
}

int envnewid()
{
   INIT_ENVIRON
   if (!environ) {
      return -1;
   }
   int i;
   for(i = 0; environ[i]; i++)
      if ((environ[i])[0] == '\0') {
         return i;
      }
   return -1;
}
