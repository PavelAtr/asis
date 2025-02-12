#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

ssize_t pipewrite(FILE* f, const void* buf, size_t count)
{
        while(f->pipbuf->writepos >= MAXPIPE) {
            if (feof(f)) {
               break;
            }
            switchtask;
        }
	size_t len = (count < MAXPIPE - f->pipbuf->writepos)?
	   count : MAXPIPE - f->pipbuf->writepos;
	memcpy(f->pipbuf->buf + f->pipbuf->writepos, buf, len);
	f->pipbuf->writepos += len;
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
INIT_FDS
   size_t ret;

   if (stream->strbuf) {
      ret = fstrwrite(ptr, size, nmemb, stream);
      goto end;
   }
   if (stream->fd != -1) {
      if (stream->pipbuf)
      {
         ret = pipewrite(stream, ptr, size * nmemb);
         goto end;
      }
   }
   ret = syscall(SYS_FWRITE, stream->file, ptr, size * nmemb, stream->pos);
end:
   stream->pos += ret;
   if (stream->pos >= stream->size) {
      stream->size = stream->pos;
   }
   if (!ret) switchtask;
   return ret;
}
