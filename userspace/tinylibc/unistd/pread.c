#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <syscall.h>
#include <errno.h>
#include <unistd.h>


ssize_t pread(int f, void* buf, size_t count, off_t offset)
{
   if (!fd_is_valid(f)) {
      errno = EBADFD;
      return -1;
   }
   size_t ret;
   if (fds[f]->stream->strbuf) {
      ret = fstrread(buf, count,  1, fds[f]->stream);
      goto end;
   }
   ret = syscall(SYS_FREAD, fds[f]->stream->file, buf, count, offset);
end:
   if (!ret) usleep(1);
   return ret;
}
