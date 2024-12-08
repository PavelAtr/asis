#include <stdio.h>

void clearerr(FILE *stream)
{
    stream->flags &= ~FILE_ERROR;
}
