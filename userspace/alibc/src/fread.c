#include <stdio.h>
#include <syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/eventfd.h>

ssize_t piperead(apipe* f, void* buf, size_t count)
{
	size_t len = (count < f->pbuf->writepos - f->pbuf->readpos)?
	   count : f->pbuf->writepos - f->pbuf->readpos;
	memcpy(buf, f->pbuf->buf + f->pbuf->readpos, len);
	f->pbuf->readpos += len;
	if (f->pbuf->readpos >= MAXPIPE) {
		f->pbuf->readpos = 0;
		f->pbuf->writepos = 0;
	}
	return len;
}

size_t fmemread(void* ptr, size_t size, size_t nmemb, amemfile* stream)
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

size_t fread(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
INIT_afds
   size_t ret;
   size_t outsize = 0;
   while (*stream->lock) {
      switchtask;
   }
   switch(stream->type)
   {
      case F_NAMEDMEM:
         ((amemfile*)stream)->membuf = asyscall(SYS_SHARED, "memfd", ((amemfile*)stream)->file, "", &outsize, 0, 0);
         stream->size = outsize;
         ret = fmemread(ptr, size,  nmemb, (amemfile*)stream);
         stream->pos += ret;
         goto end;
         break;
      case F_MEM:
         ret = fmemread(ptr, size, nmemb, (amemfile*)stream);
         ((amemfile*)stream)->pos += ret;
         goto end;
         break;
      case F_PIPE:
         ret = piperead((apipe*)stream, ptr, size * nmemb);
         goto end;
         break;
      case F_FILE:   
         ret = (size_t)asyscall(SYS_FREAD, stream->file, ptr, size * nmemb, stream->pos, 0, 0);
         stream->pos += ret;
      case F_EVENTFD:
         if (((aeventfd*)stream)->value == 0) {
            errno = EAGAIN;
            return -1;
         }
         if (((aeventfd*)stream)->flags & EFD_SEMAPHORE) {
            unsigned long value = 1;
            memcpy(ptr, &value, sizeof(uint64_t));
            *((aeventfd*)stream)->value -= 1;
         } else {
            memcpy(ptr, ((aeventfd*)stream)->value, sizeof(uint64_t));
            *((aeventfd*)stream)->value = 0;
         }
         return sizeof(uint64_t);
      case F_TIMERFD:
         struct timespec now;
/* stub time NOT REALIZED*/
            if (nmemb * size >= sizeof(uint64_t)) {
               *(uint64_t*)ptr = ((atimerfd*)stream)->expirations;
               ((atimerfd*)stream)->expirations = 0;
                  return sizeof(uint64_t);
            }
            errno = EINVAL;
            return -1;
/* stub time NOT REALIZED*/
         clock_gettime(CLOCK_REALTIME, &now);
         if ((now.tv_sec > ((atimerfd*)stream)->next_expiry.tv_sec) ||
            (now.tv_sec == ((atimerfd*)stream)->next_expiry.tv_sec && now.tv_nsec >= ((atimerfd*)stream)->next_expiry.tv_nsec)) {
            ((atimerfd*)stream)->expirations++;
            // Перезапуск периодического таймера
            if (((atimerfd*)stream)->spec.it_interval.tv_sec || ((atimerfd*)stream)->spec.it_interval.tv_nsec) {
               ((atimerfd*)stream)->next_expiry.tv_sec += ((atimerfd*)stream)->spec.it_interval.tv_sec;
               ((atimerfd*)stream)->next_expiry.tv_nsec += ((atimerfd*)stream)->spec.it_interval.tv_nsec;                  
               if (((atimerfd*)stream)->next_expiry.tv_nsec >= 1000000000) {
                  ((atimerfd*)stream)->next_expiry.tv_sec += 1;
                  ((atimerfd*)stream)->next_expiry.tv_nsec -= 1000000000;
               }
            }
            if (nmemb * size >= sizeof(uint64_t)) {
               *(uint64_t*)ptr = ((atimerfd*)stream)->expirations;
               ((atimerfd*)stream)->expirations = 0;
                  return sizeof(uint64_t);
            }
            errno = EINVAL;
            return -1;
         }
         errno = EAGAIN;
         return -1;
      default:
         break; 
   }
end:
   if (!ret) switchtask;
   return ret;
}
