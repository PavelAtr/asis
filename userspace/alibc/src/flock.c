#include <stdio.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/file.h>

int flock(int f, int operation)
{
   INIT_afds
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   switch(operation) {
      case LOCK_SH:
      case LOCK_EX:
         while(*afds[f]->lock) switchtask;
         *afds[f]->lock = 1;
         break;
      case LOCK_NB:
         if (*afds[f]->lock) {
            errno = EWOULDBLOCK;
            return -1;
         }
      case LOCK_UN:
         *afds[f]->lock = 0;
         break;
   }
   return 0;
}

