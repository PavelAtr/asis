/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <string.h>
#include <syscall.h>
#include <stdio.h>
#ifndef UEFI
#include <stdlib.h>
#endif
#ifdef __ASIS__
#include <asis.h>
#endif

char lock = 0;

void initfile(FILE* src)
{
   src->fd = -1; // File descriptor not set
   src->lock = malloc(sizeof(char));
   *src->lock = 0;
   src->fd_refcount = 1;
   if (src->type & F_FILE || src->type & F_PIPE || src->type & F_NAMEDPIPE
       || src->type & F_MEM || src->type & F_NAMEDMEM) {
       src->file = NULL;
       src->mode = NULL;
       src->flags = 0;
       src->pos = 0;
       src->size = 0;
   }
}

void copyfile(FILE** dst, FILE* src)
{
   if (!dst || !src) {
           return;
   }
   switch(src->type) {
      case F_FILE:
         *dst = calloc(1, sizeof(FILE));
         memcpy(*dst, src, sizeof(FILE));
         break;
      case F_NAMEDPIPE:
         *dst = calloc(1, sizeof(anamedpipe));
         memcpy(*dst, src, sizeof(anamedpipe));
         ((apipe*)*dst)->pbuf->refcount++;
         break;
      case F_PIPE:
         *dst = calloc(1, sizeof(apipe));
         memcpy(*dst, src, sizeof(apipe));
         ((apipe*)*dst)->pbuf->refcount++;
         break;
      case F_MEM:
      case F_NAMEDMEM:
         *dst = calloc(1, sizeof(amemfile));
         memcpy(*dst, src, sizeof(amemfile));
         break;
      case F_DIR:
         break;
      case F_SOCKET:
         *dst = calloc(1, sizeof(asocket));
         memcpy(*dst, src, sizeof(asocket));
         ((asocket*)*dst)->pending = (void**)malloc(sizeof(void*) * UNIX_LISTEN_BACKLOG);
         memcpy(((asocket*)*dst)->pending,
            ((asocket*)src)->pending, sizeof(void*) * UNIX_LISTEN_BACKLOG);
         break;
      case F_EVENTFD:
         *dst = calloc(1, sizeof(aeventfd));
         memcpy(*dst, src, sizeof(aeventfd));
         break;
      case F_TIMERFD:
         *dst = calloc(1, sizeof(atimerfd));
         memcpy(*dst, src, sizeof(atimerfd));
         break;
      default:
         return;
   }
   (*dst)->fd_refcount++;
   if (src->type & F_FILE || src->type & F_PIPE || src->type & F_NAMEDPIPE
       || src->type & F_MEM || src->type & F_NAMEDMEM) {
      if (src->file)
         (*dst)->file = strdup(src->file); // Copy the file name
      if (src->mode)
         (*dst)->mode = strdup(src->mode); // Copy the mode
   }
};

void freefile(FILE* dst)
{
   if (!dst) {
           return;
   }
   switch(dst->type) {
      case F_FILE:
         break;
      case F_NAMEDPIPE:
         #ifdef __ASIS__
         sys_delshared("fifo", dst->file);
         #else
         asyscall(SYS_FREESHARED, "fifo", dst->file, 0, 0, 0, 0);
         #endif
         break;
      case F_PIPE:
         if (((apipe*)dst)->pbuf && ((apipe*)dst)->pbuf->refcount <= 1) {
            free(((apipe*)dst)->pbuf);
         }
         ((apipe*)dst)->pbuf->refcount--;
         break;
      case F_MEM:
/*         if (((amemfile*)dst)->membuf && dst->fd_refcount <= 1) {
            // Free the memory buffer if it exists and refcount is 1 or less
            free(((amemfile*)dst)->membuf);
            ((amemfile*)dst)->membuf = NULL;
         }*/
         break;
      case F_NAMEDMEM:
         #ifdef __ASIS__
         sys_delshared("memfd", dst->file);
         #else
         asyscall(SYS_FREESHARED, "memfd", dst->file, 0, 0, 0, 0);
         #endif
         break;
      case F_DIR:
         break;
      case F_SOCKET:
         if (((asocket*)dst)->pending) {
            free(((asocket*)dst)->pending);
         }
         break;
      case F_EVENTFD:
         if (((aeventfd*)dst)->value && dst->fd_refcount <= 1) {
            free(((aeventfd*)dst)->value); // Free the timer file descriptor value pointer
         }
         break;
      default:
         break;
   } 
   if (dst->type & F_FILE || dst->type & F_PIPE || dst->type & F_NAMEDPIPE
       || dst->type & F_MEM || dst->type & F_NAMEDMEM) {
      if (dst->file) {
         free(dst->file);
         dst->file = NULL;
      }
   }
   dst->fd_refcount--;
   free(dst);
};
