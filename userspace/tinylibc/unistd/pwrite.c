#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <errno.h>

ssize_t pwrite(int f, const void* buf, size_t count, off_t offset) {
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   size_t ret;
   if (fds[f].stream->strbuf) {
      ret = fstrwrite(buf, count, 1, fds[f].stream);
      goto end;
   }
   ret = syscall(SYS_FWRITE, fds[f].stream->file, buf, count, offset);
end:
//    if (!ret) usleep(1);
   return ret;
}
