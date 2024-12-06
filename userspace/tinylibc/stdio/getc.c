#include <stdio.h>
#include <unistd.h>

int getc(FILE* stream)
{
    int ret;
    ret = fread(&ret, 1, 1, stream);
    if (ret == 0) return EOF;
    return ret;
}
