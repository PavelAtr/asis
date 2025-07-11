#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

int fcntl(int fd, int cmd, ... /* arg */ )
{
   INIT_afds
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
               afds[fd]->flags |= flags;
               break;
            default:
               break;
         }
         return 0;
      case F_SETLK:
         /* NOT REALIZED */
         return 0;
      case F_DUPFD:
      case F_DUPFD_CLOEXEC:
         int newfd = va_arg(vl, int);
         va_end(vl);
         int ret = dup2(fd, newfd);
         if (cmd == F_DUPFD_CLOEXEC && ret != -1) {
            afds[ret]->flags |= FD_CLOEXEC;
         }
         return ret;
      default:
         break;
   }
   return -1;
}
