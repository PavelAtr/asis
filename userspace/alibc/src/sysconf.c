#include <syscall.h>
#include <fcntl.h>
#include <unistd.h>

long sysconf(int name)
{
   switch (name) {
   case _SC_OPEN_MAX:
      return (long)asyscall(SYS_GETMAXFD, 0, 0, 0, 0, 0, 0);
   case _SC_CLK_TCK:
      return 1000;
   case _SC_NGROUPS_MAX:
      return 1000;
   default:
      break;
   }

   return 0;
}