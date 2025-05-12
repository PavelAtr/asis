#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

ssize_t piperead(FILE* f, void* buf, size_t count)
{
	size_t len = (count < f->pipbuf->writepos - f->pipbuf->readpos)?
	   count : f->pipbuf->writepos - f->pipbuf->readpos;
	memcpy(buf, f->pipbuf->buf + f->pipbuf->readpos, len);
	f->pipbuf->readpos += len;
	if (f->pipbuf->readpos >= MAXPIPE) {
		f->pipbuf->readpos = 0;
		f->pipbuf->writepos = 0;
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
INIT_FDS
   size_t ret;
   if (stream->strbuf) {
      ret = fstrread(ptr, size,  nmemb, stream);
      goto end;
   }
   if (stream->fd != -1) {
      if (stream->pipbuf)
      {
         ret = piperead(stream, ptr, size * nmemb);
         goto end;
      }
   }
   ret = syscall(SYS_FREAD, stream->file, ptr, size * nmemb, stream->pos);
end:
   stream->pos += ret;
   if (!ret) switchtask;
   return ret;
}
