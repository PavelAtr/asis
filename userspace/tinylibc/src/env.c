#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>
#include <errno.h>

char** environ;

int envid(const char *name)
{
   INIT_ENVIRON
   int i;
   for(i = 0; environ[i] != NULL; i++)
      if (strstr(environ[i], name) == environ[i]
         && (environ[i])[strlen(name)] == '=') {
         return i;
      }
   return -1;
}

int envnewid()
{
   INIT_ENVIRON
   int i;
   for(i = 0; environ[i] != NULL; i++)
      if ((environ[i])[0] == '\0') {
         return i;
      }
   return -1;
}
