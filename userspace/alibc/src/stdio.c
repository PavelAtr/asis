#include <string.h>
#ifndef UEFI
#include <stdio.h>
#include <stdlib.h>
#endif
#ifdef __ASIS__
#include <asis.h>
#endif

__thread FILE** fds;

void initfile(FILE* src)
{
        memset(src, 0x0, sizeof(FILE));
        src->fd = -1;
}

void copyfile(FILE* dst, FILE* src)
{
   if (!dst || !src) {
           return;
   }
   memcpy(dst, src, sizeof(FILE));
   size_t filelen = strlen(src->file) + 1;
   dst->file = malloc(filelen);
   memcpy(dst->file, src->file, filelen);
   
   if (src->strbuf) {
      dst->strbuf = malloc(src->size);
   }

   if (src->pipbuf) {
      src->pipbuf->nlink++;
   }
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
   if (dst->strbuf) {
      dst->strbuf = NULL;
   }
   if (dst->pipbuf) {
      dst->pipbuf->nlink--;
      if (dst->pipbuf->nlink <= 0) {
         free(dst->pipbuf);
         dst->pipbuf = NULL;
      }
   }
   free(dst);
};
