#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>
#include <errno.h>

int envid(const char *name)
{
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
   int i;
   for(i = 0; environ[i]; i++)
      if ((environ[i])[0] == '\0') {
         return i;
      }
   return -1;
}
