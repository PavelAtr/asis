#include <stdio.h>
#include <fcntl.h>
#include <syscall.h>
#include <string.h>

char *ttyname(int fd)
{
   INIT_afds
   if (!fd_is_valid(fd)) {
      return NULL;
   }
   return strdup(afds[fd]->file);
}

int ttyname_r(int fd, char buf[], size_t buflen)
{
   INIT_afds
   if (!fd_is_valid(fd)) {
      return -1;
   }
   memset(buf, 0x0, buflen);
   strncpy(buf, afds[fd]->file, buflen);
}
