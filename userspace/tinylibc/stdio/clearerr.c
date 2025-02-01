#include <stdio.h>

void clearerr(FILE *stream)
{
INIT_FDS
   stream->flags &= ~FILE_ERROR;
}
