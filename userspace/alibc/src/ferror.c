#include <stdio.h>

int ferror(FILE *stream)
{
INIT_FDS
   if (stream->flags & FILE_ERROR) {
      return 1;
   }
   return 0;
}