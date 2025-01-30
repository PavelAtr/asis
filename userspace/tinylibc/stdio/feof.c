#include <stdio.h>

int feof(FILE *stream)
{
   if (stream->pipbuf) {
      if (stream->pipbuf->feof) {
         return 1;
      }
   }
   if (stream->flags & FILE_INFINITY) {
      return 0;
   }
   if (stream->pos >= stream->size) {
      return 1;
   }
   return 0;
}
