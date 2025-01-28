#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

ssize_t pipewrite(int f, const void* buf, size_t count)
{
	fdesc* fd = fds[f];
	size_t len = (count < MAXPIPE - fd->wpipe->writepos)?
	   count : MAXPIPE - fd->wpipe->writepos;
	memcpy(fd->wpipe->buf + fd->wpipe->writepos, buf, len);
	fd->wpipe->writepos += len;
	if (!len) {
		usleep(1);
	}
	return len;
}

size_t fstrwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream)
{
   size_t len = size * nmemb;
   size_t ret = (stream->pos + len > stream->size)? stream->size - stream->pos:
      len;
   size_t i;
   for (i = 0; i < ret; i++) {
      stream->strbuf[i] = ((char*) ptr)[stream->pos + i];
   }
   return ret;
}

size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream)
{
   size_t ret;

   if (stream->strbuf) {
      ret = fstrwrite(ptr, size, nmemb, stream);
      goto end;
   }
   if (stream->fd != -1) {
      if (!fd_is_valid(stream->fd)) {
		errno = EBADFD;
		return -1;
	  }
	  if (fds[stream->fd]->wpipe)
	  {
		  ret = pipewrite(stream->fd, ptr, size * nmemb);
		  goto end;
	  }
   }
   ret = syscall(SYS_FWRITE, stream->file, ptr, size * nmemb, stream->pos);
end:
   stream->pos += ret;
   if (stream->pos >= stream->size) {
      stream->size = stream->pos;
   }
   if (!ret) usleep(1);
   return ret;
}
