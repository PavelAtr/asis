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
         memset(src, 0, sizeof(apipe)); // Initialize the FILE structure
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
         memset(src, 0, sizeof(aeventfd)); // Initialize the timer file descriptor structure
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
      case F_PIPE:
         memcpy(dst, src, sizeof(apipe));
         ((apipe*)dst)->pbuf->refcount++;
         break;
      case F_MEM:
      case F_NAMEDMEM:
         memcpy(dst, src, sizeof(amemfile));
         ((amemfile*)dst)->fd_refcount++;
         break;
      case F_DIR:
         break;
      case F_SOCKET:
         memcpy(dst, src, sizeof(asocket));
         ((asocket*)dst)->pending = (void**)malloc(sizeof(void*) * UNIX_LISTEN_BACKLOG);
         memcpy(((asocket*)dst)->pending, ((asocket*)src)->pending, sizeof(void*) * UNIX_LISTEN_BACKLOG);
         break;
      case F_EVENTFD:
         memset(src, 0, sizeof(aeventfd)); // Initialize the timer file descriptor structure
         ((aeventfd*)dst)->fd_refcount++;
         break;
      default:
         return;
   }
   dst->file = strdup(src->file); // Copy the file name
   dst->mode = strdup(src->mode); // Copy the mode
};

void freefile(FILE* dst)
{
   if (!dst) {
           return;
   }
   if (dst->file) {
      free(dst->file);
      dst->file = NULL;
   }
   switch(dst->type) {
      case F_FILE:
         break;
      case F_PIPE:
         if (((apipe*)dst)->pbuf && ((apipe*)dst)->pbuf->refcount <= 1) {
            size_t size = 0;
            #ifdef __ASIS__
            
            if (sys_shared("pipe", dst->file, "", &size)) {
               free(((apipe*)dst)->pbuf);
            } else {
               sys_delshared("pipe", dst->file);
            }
            #else
            if (!asyscall(SYS_SHARED, "pipe", dst->file, "", &size, 0, 0)) {
               free(((apipe*)dst)->pbuf);
            } else {
               asyscall(SYS_FREESHARED, "pipe", dst->file, 0, 0, 0, 0);
            }
            #endif
         }
         ((apipe*)dst)->pbuf->refcount--;
         break;
      case F_MEM:
      case F_NAMEDMEM:
         if (((amemfile*)dst)->membuf && ((amemfile*)dst)->fd_refcount <= 1) {
            // Free the memory buffer if it exists and refcount is 1 or less
            free(((amemfile*)dst)->membuf);
            ((amemfile*)dst)->membuf = NULL;
         }
         ((amemfile*)dst)->fd_refcount--;
         break;
      case F_DIR:
         break;
      case F_SOCKET:
         if (((asocket*)dst)->pending) {
            free(((asocket*)dst)->pending);
         }
         break;
      case F_EVENTFD:
         if (((aeventfd*)dst)->value && ((aeventfd*)dst)->fd_refcount <= 1) {
            free(((aeventfd*)dst)->value); // Free the timer file descriptor value pointer
         }
         ((aeventfd*)dst)->fd_refcount--;
         break;
      default:
         break;
   } 
   free(dst);
};
