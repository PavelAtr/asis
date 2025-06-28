#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>
#include <errno.h>

int envid(const char *name);

int unsetenv(const char *name)
{
   INIT_ENVIRON
   int i = envid(name);
   if (i == -1) {
      errno = ENOENT;
      return -1;
   }
   environ[i] = strdup("");
   return 0;
}
