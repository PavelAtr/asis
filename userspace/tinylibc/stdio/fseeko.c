#include <stdio.h>
#include <unistd.h>

int fseeko(FILE *stream, off_t offset, int whence)
{
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
