#include <stdio.h>

char * fgetln (FILE *stream, size_t *len)
{
INIT_afds
    char* s = NULL;
    getdelim(&s, len, '\n', stdin);
    return s;
}
