#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

ssize_t piperead(FILE* f, void* buf, size_t count)
{
	size_t len = (count < f->rpipe->writepos - f->rpipe->readpos)?
	   count : f->rpipe->writepos - f->rpipe->readpos;
	memcpy(buf, f->rpipe->buf, len);
	f->rpipe->readpos += len;
	if (f->rpipe->readpos = MAXPIPE) {
		f->rpipe->readpos = 0;
		f->rpipe->writepos = 0;
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
	  if (stream->rpipe)
	  {
		  ret = piperead(stream, ptr, size * nmemb);
		  goto end;
	  }
   }
   ret = syscall(SYS_FREAD, stream->file, ptr, size * nmemb, stream->pos);
end:
   stream->pos += ret;
   if (!ret) usleep(1);
   return ret;
}
