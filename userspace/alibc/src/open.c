#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int open(const char *pathname, int flags, ...)
{
   INIT_afds
   mode_t mode = 0;
   if (flags & O_CREAT) {
      mode = S_IFREG | 0666 & ~gmask;
      mknod(pathname, mode, 0);
   }
   if (flags & O_TRUNC) {
      truncate(pathname, 0);
   }
   int fd = get_free_fd();
   if (fd == -1) {
      errno = ENOMEM;
      return -1;
   }
   afds[fd] = fopen(pathname,  "r+");
   if (!afds[fd]) {
      errno = ENOENT;
      return -1;
   }
   if (flags & O_APPEND) {
      afds[fd]->pos = afds[fd]->size;
   }
   afds[fd]->fdflags = flags;
   afds[fd]->fd = fd;
   return fd;
}
