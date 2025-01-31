#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>
#include <errno.h>

extern char*** environ;

int envid(const char *name);
int envnewid();

int unsetenv(const char *name)
{
   int i = envid(name);
   if (i == -1) {
      errno = ENOENT;
      return -1;
   }
   (*environ)[i] = "";
   return 0;
}
