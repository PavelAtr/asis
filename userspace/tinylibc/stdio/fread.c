#include <stdio.h>
#include <syscall.h>
#include <unistd.h>

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
   ret = syscall(SYS_FREAD, stream->file, ptr, size * nmemb, stream->pos);
   stream->pos += ret;
end:
   if (!ret) usleep(1);
   return ret;
}
