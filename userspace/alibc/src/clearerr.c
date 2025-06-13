#include <stdio.h>

void clearerr(FILE *stream)
{
INIT_afds
   stream->flags &= ~FILE_ERROR;
}
