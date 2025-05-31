#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <syscall.h>

int ioctl(int fd, unsigned long request, ...)
{
   INIT_FDS
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
   va_list vl;
   va_start(vl, request);
   switch (request) {
	case FICLONE:
	    int srcfd = va_arg(vl, int);
	    int destfd = fd;
	    return dup2(srcfd, destfd);
   }
   long ret = asyscall(SYS_IOCTL, fds[fd]->file, request, &vl, 0, 0, 0);
   va_end(vl);
   return ret;
}