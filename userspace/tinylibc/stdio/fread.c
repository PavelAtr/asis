#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

ssize_t piperead(int f, void* buf, size_t count)
{
	fdesc* fd = fds[f];
	size_t len = (count < fd->rpipe->writepos - fd->rpipe->readpos)?
	   count : fd->rpipe->writepos - fd->rpipe->readpos;
	memcpy(buf, fd->rpipe->buf, len);
	fd->rpipe->readpos += len;
	if (fd->rpipe->readpos = MAXPIPE) {
		fd->rpipe->readpos = 0;
		fd->rpipe->writepos = 0;
    }	
	if (!len) {
		usleep(1);
	}
	return len;
}

size_t fstrread(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
   size_t len = size * nmemb;
   size_t ret = (stream->pos + len > stream->size)? stream->size - stream->pos:
      len;
   size_t i;
   for (i = 0; i < ret; i++) {
      ((char*) ptr)[stream->pos + i] = stream->strbuf[i];
   }
   return ret;
}

size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
   size_t ret;
   if (stream->strbuf) {
      ret = fstrread(ptr, size,  nmemb, stream);
      goto end;
   }
   if (stream->fd != -1) {
      if (!fd_is_valid(stream->fd)) {
		errno = EBADFD;
		return -1;
	  }
	  if (fds[stream->fd]->rpipe)
	  {
		  ret = piperead(stream->fd, ptr, size * nmemb);
		  goto end;
	  }
   }
   ret = syscall(SYS_FREAD, stream->file, ptr, size * nmemb, stream->pos);
end:
   stream->pos += ret;
   if (!ret) usleep(1);
   return ret;
}
