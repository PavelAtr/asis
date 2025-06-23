/******************************************************
 *  Author: Pavel V Samsonov 2025
 *******************************************************/

#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

ssize_t pipewrite(apipe *f, const void *buf, size_t count)
{
   size_t len = (count < MAXPIPE - f->pbuf->writepos) ? count : MAXPIPE - f->pbuf->writepos;
   memcpy(f->pbuf->buf + f->pbuf->writepos, buf, len);
   f->pbuf->writepos += len;
   return len;
}

size_t fmemwrite(const void *ptr, size_t size, size_t nmemb, amemfile *stream)
{
   const char *tmp =ptr;
   size_t len = size * nmemb;
   size_t ret = (stream->pos + len > stream->size) ? stream->size - stream->pos : len;
   size_t i;
   for (i = 0; i < ret; i++)
   {
      stream->membuf[stream->pos + i] = ((char *)ptr)[i];
   }
   return ret;
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
   INIT_afds
       size_t ret;
   while (*stream->lock)
   {
      switchtask;
   }
   switch (stream->type)
   {
   case F_NAMEDMEM:
      size_t outsize = stream->pos + size * nmemb;
      if (asyscall(SYS_SHARED, &((amemfile *)stream)->membuf,"memfd", stream->file, "", &outsize, 0))
      {
	stream->flags |= FILE_ERROR;
	return 0;
      }
      stream->size = outsize;
      ret = fmemwrite(ptr, size, nmemb, (amemfile *)stream);
      stream->pos += ret;
      goto end;
      break;
   case F_MEM:
      size_t s = stream->pos + size * nmemb;
      if (s > stream->size & stream->flags & FILE_RESIZEBLE)
      {
         char *new_mem = malloc(s);
         if (!new_mem)
         {
            errno = ENOMEM;
            ret = 0;
            goto end;
         }
         memcpy(new_mem, ((amemfile *)stream)->membuf, stream->size);
         free(((amemfile *)stream)->membuf);
         ((amemfile *)stream)->membuf = new_mem;
         stream->size = s;
         *((amemfile *)stream)->clientptr = new_mem;
         *((amemfile *)stream)->clientsize = s;
      }
      ret = fmemwrite(ptr, size, nmemb, (amemfile *)stream);
      stream->pos += ret;
      goto end;
      break;
   case F_NAMEDPIPE:
      ret = pipewrite((anamedpipe *)stream, ptr, size * nmemb);
      goto end;
      break;
   case F_PIPE:
      ret = pipewrite((apipe *)stream, ptr, size * nmemb);
      goto end;
      break;
   case F_FILE:
      ret = (size_t)asyscall(SYS_FWRITE, stream->file, ptr, size * nmemb, stream->pos, 0, 0);
      stream->pos += ret;
      goto end;
      break;
   case F_EVENTFD:
      memcpy(((aeventfd *)stream)->value, ptr, sizeof(uint64_t));
      return sizeof(uint64_t);
   default:
      break;
   }
end:
   if (!ret)
      switchtask;
   return ret;
}
