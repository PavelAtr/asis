#include <stdio.h>

int ferror(FILE *stream)
{
    if (stream->flags & FILE_ERROR)
	return 1;
    return 0;
}