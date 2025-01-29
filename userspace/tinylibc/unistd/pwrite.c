#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <errno.h>
#include <unistd.h>

ssize_t pwrite(int f, const void* buf, size_t count, off_t offset) {
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   size_t ret;
   if (fds[f]->strbuf) {
      ret = fstrwrite(buf, count, 1, fds[f]);
      goto end;
   }
   ret = syscall(SYS_FWRITE, fds[f]->file, buf, count, offset);
end:
   if (!ret) usleep(1);
   return ret;
}
