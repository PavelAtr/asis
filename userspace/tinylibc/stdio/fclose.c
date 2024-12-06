#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fclose(FILE *stream)
{
    free(stream->file);
    free(stream);
    stream = NULL;
    return 0;
}
