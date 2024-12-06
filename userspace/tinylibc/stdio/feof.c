#include <stdio.h>

int feof(FILE *stream)
{
    if (stream->flags & FILE_INFINITY)
		return 0;
    if (stream->flags & FILE_EOF)
		return 1;
    return 0;
}
