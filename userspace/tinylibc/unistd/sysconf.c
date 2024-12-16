#include <syscall.h>
#include <fcntl.h>
#include <unistd.h>

long sysconf(int name)
{
   switch (name) {
   case _SC_OPEN_MAX:
      return MAXFD;
      break;
   default:
      break;
   }

   return 0;
}