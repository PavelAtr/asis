#include <string.h>
#include <syscall.h>
#include <stdio.h>
#ifndef UEFI
#include <stdlib.h>
#endif
#ifdef __ASIS__
#include <asis.h>
#endif

void initfile(FILE* src)
{
   src->fd = -1; // File descriptor not set
   switch(src->type) {
      case F_FILE:
         memset(src, 0, sizeof(FILE)); // Initialize the FILE structure
         break;
      case F_PIPE:
         memset(src, 0, sizeof(apipe)); // Initialize the pipe structure
         break;
      case F_NAMEDPIPE:
         memset(src, 0, sizeof(anamedpipe)); // Initialize the pipe structure
         break;
      case F_MEM:
      case F_NAMEDMEM:
         memset(src, 0, sizeof(amemfile)); // Initialize the named memory file structure
         break;
      case F_DIR:
         break;
      case F_SOCKET:
         memset(src, 0, sizeof(asocket)); // Initialize the socket structure
         break;
      case F_EVENTFD:
         memset(src, 0, sizeof(aeventfd)); // Initialize the event file descriptor structure
         break;
      case F_TIMERFD:
         memset(src, 0, sizeof(atimerfd)); // Initialize the timer file descriptor structure)
         break;
      default:
         break;
   }
   src->lock = calloc(1, sizeof(char));
   src->fd_refcount = 1;
}

void copyfile(FILE* dst, FILE* src)
{
   if (!dst || !src) {
           return;
   }
   switch(src->type) {
      case F_FILE:
         memcpy(dst, src, sizeof(FILE));
         break;
      case F_NAMEDPIPE:
         memcpy(dst, src, sizeof(anamedpipe));
         ((apipe*)dst)->pbuf->refcount++;
         break;
      case F_PIPE:
         memcpy(dst, src, sizeof(apipe));
         ((apipe*)dst)->pbuf->refcount++;
         break;
      case F_MEM:
      case F_NAMEDMEM:
         memcpy(dst, src, sizeof(amemfile));
         break;
      case F_DIR:
         break;
      case F_SOCKET:
         memcpy(dst, src, sizeof(asocket));
         ((asocket*)dst)->pending = (void**)malloc(sizeof(void*) * UNIX_LISTEN_BACKLOG);
         memcpy(((asocket*)dst)->pending, ((asocket*)src)->pending, sizeof(void*) * UNIX_LISTEN_BACKLOG);
         break;
      case F_EVENTFD:
         memcpy(dst, src, sizeof(aeventfd));
         break;
      case F_TIMERFD:
         memcpy(dst, src, sizeof(atimerfd));
         break;
      default:
         return;
   }
   dst->fd_refcount++;
   dst->file = strdup(src->file); // Copy the file name
   dst->mode = strdup(src->mode); // Copy the mode
};

void freefile(FILE* dst)
{
   if (!dst) {
           return;
   }
   if (dst->type & F_FILE || dst->type & F_PIPE || dst->type & F_NAMEDPIPE
       || dst->type & F_MEM || dst->type & F_NAMEDMEM) {
      if (dst->file) {
         free(dst->file);
         dst->file = NULL;
      }
   }
   switch(dst->type) {
      case F_FILE:
         break;
      case F_NAMEDPIPE:
         if (((apipe*)dst)->pbuf && ((apipe*)dst)->pbuf->refcount <= 1) {
            #ifdef __ASIS__
               sys_delshared("pipe", dst->file);
            #else
               asyscall(SYS_FREESHARED, "pipe", dst->file, 0, 0, 0, 0);
            #endif
         }
         ((apipe*)dst)->pbuf->refcount--;
         break;
      case F_PIPE:
         if (((apipe*)dst)->pbuf && ((apipe*)dst)->pbuf->refcount <= 1) {
            free(((apipe*)dst)->pbuf);
         }
         ((apipe*)dst)->pbuf->refcount--;
         break;
      case F_MEM:
         if (((amemfile*)dst)->membuf && dst->fd_refcount <= 1) {
            // Free the memory buffer if it exists and refcount is 1 or less
            free(((amemfile*)dst)->membuf);
            ((amemfile*)dst)->membuf = NULL;
         }
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
   dst->fd_refcount--;
   free(dst);
};
