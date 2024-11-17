#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fclose(FILE *stream)
{
    free(stream->file);
    free(stream);
    return 0;
}
