#include <stdio.h>
#include <unistd.h>

int fseek(FILE* stream, long offset, int whence)
{
INIT_afds
   switch (whence) {
   case SEEK_SET:
      stream->pos = offset;
      break;
   case SEEK_CUR:
      stream->pos += offset;
      break;
   case SEEK_END:
      stream->pos = stream->size - offset;
      break;
   }
   return 0;
}
