#include <stdio.h>

int ferror(FILE *stream)
{
INIT_afds
   if (stream->flags & FILE_ERROR) {
      return 1;
   }
   return 0;
}