#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

ssize_t pipewrite(apipe* f, const void* buf, size_t count)
{
	size_t len = (count < MAXPIPE - f->pbuf->writepos)?
	   count : MAXPIPE - f->pbuf->writepos;
	memcpy(f->pbuf->buf + f->pbuf->writepos, buf, len);
	f->pbuf->writepos += len;
	return len;
}

size_t fmemwrite(const void* ptr, size_t size, size_t nmemb, amemfile* stream)
{
   size_t len = size * nmemb;
   size_t ret = (stream->pos + len > stream->size)? stream->size - stream->pos:
      len;
   size_t i;
   for (i = 0; i < ret; i++) {
      stream->membuf[i] = ((char*) ptr)[stream->pos + i];
   }
   return ret;
}

size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream)
{
INIT_afds
   size_t ret;
   while (*stream->lock) {
      switchtask;
   }
   switch(stream->type)
   {
      case F_NAMEDMEM:
         size_t outsize = ((amemfile*)stream)->pos + size * nmemb;
         ((amemfile*)stream)->membuf = asyscall(SYS_SHARED, "memfd", ((amemfile*)stream)->file, "", &outsize, 0, 0);
         ((amemfile*)stream)->size = outsize;
         ret = fmemwrite(ptr, size,  nmemb, (amemfile*)stream);
         ((amemfile*)stream)->pos += ret;
         goto end;
         break;
      case F_MEM:
         ret = fmemwrite(ptr, size, nmemb, (amemfile*)stream);
         ((amemfile*)stream)->pos += ret;
         goto end;
         break;
      case F_PIPE:
         ret = pipewrite((apipe*)stream, ptr, size * nmemb);
         goto end;
         break;
      case F_FILE:   
         ret = (size_t)asyscall(SYS_FWRITE, ((FILE*)stream)->file, ptr, size * nmemb, stream->pos, 0, 0);
         stream->pos += ret;
         goto end;
         break;
      case F_EVENTFD:
         memcpy(((aeventfd*)stream)->value, ptr, sizeof(uint64_t));
         return sizeof(uint64_t);         
      default:
         break; 
   }
end:
   if (!ret) switchtask;
   return ret;
}
