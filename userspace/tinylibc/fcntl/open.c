#include <fcntl.h>
#include <stdio.h>
#include <syscall.h>
#include <errno.h>
#include <tiny.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int open(const char *pathname, int flags, ...)
{
  mode_t mode = 0;
  if (flags & O_CREAT) {
    mode = S_IFREG | 0666 & ~global_mask;
    mknod(pathname, mode, 0);
  }
  if (flags & O_TRUNC)
    truncate(pathname, 0);
  int fd = get_free_fd();
  if (fd == -1) {
    set_errno(ENOMEM);
    return -1;
  }
  FILE* f = fopen(pathname,  "r+");
  if (!f) {
    set_errno(ENOENT);
    return -1;
  }
  fds[fd].stream = f;
  if (flags & O_APPEND)
    fds[fd].stream->pos = fds[fd].stream->size;
  fds[fd].flags = flags;
  fds[fd].rpipe = NULL;
  fds[fd].wpipe = NULL;
  return fd;
}
