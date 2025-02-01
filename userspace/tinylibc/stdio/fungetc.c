#include <stdio.h>
#include <unistd.h>

int ungetc(int c, FILE *stream)
{
INIT_FDS
   stream->pos = (stream->pos == 0) ? 0: stream->pos - 1;
   return c;
}
