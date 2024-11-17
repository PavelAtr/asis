#include <stdio.h>
#include <unistd.h>

int getc(FILE* stream)
{
    int ret;
    fread(&ret, 1, 1, stream);
    return ret;
}
