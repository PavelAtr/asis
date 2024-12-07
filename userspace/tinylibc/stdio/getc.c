#include <stdio.h>
#include <unistd.h>

int getc(FILE* stream)
{
    int ret;
    size_t len = fread(&ret, 1, 1, stream);
    if (len == 0) return EOF;
    return ret;
}
