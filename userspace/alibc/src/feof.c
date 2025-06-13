#include <stdio.h>

int feof(FILE *stream)
{
INIT_afds
   if (stream->pipbuf) {
      if (stream->pipbuf->nlink <= 1)
      return 1;
   }
   if (stream->flags & FILE_INFINITY) {
      return 0;
   }
   if (stream->pos >= stream->size - 1) {
      return 1;
   }
   return 0;
}
