#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <syscall.h>

int fcntl(int fd, int cmd, ... /* arg */ )
{
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
   va_list vl;
   va_start(vl, cmd);
   switch (cmd) {
      case F_GETFL:
         /* NOT REALIZED */
         return O_RDWR;
      case F_SETFD:
         int flags = va_arg(vl, int);
         va_end(vl);
         switch(flags) {
            case FD_CLOEXEC:
               fds[fd].flags |= flags;
               break;
            default:
               break;
         }
         return 0;
      case F_SETLK:
         /* NOT REALIZED */
         return 0;
      default:
         break;
   }
   return -1;
}
