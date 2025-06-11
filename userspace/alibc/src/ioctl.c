#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <syscall.h>

int aioctl(int fd, unsigned long request, void* arg1, void* arg2, void* arg3, void* arg4)
{
   INIT_FDS
   if (!fd_is_valid(fd)) {
      errno = EBADFD;
      return -1;
   }
   switch (request) {
	case FICLONE:
	    int srcfd =(int) arg1;
	    int destfd = fd;
	    return dup2(srcfd, destfd);
	default:
	    break;
   }
   int ret = (int)asyscall(SYS_IOCTL, fds[fd]->file, request, arg1, arg2, arg3, arg4);
   return ret;
}
