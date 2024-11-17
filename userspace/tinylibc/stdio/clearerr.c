#include <stdio.h>

void clearerr(FILE *stream)
{
    stream->flags &= ~FILE_EOF;
    stream->flags &= ~FILE_ERROR;
}
