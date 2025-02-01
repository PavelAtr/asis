#include <stdio.h>

int fputc(int c, FILE *stream)
{
INIT_FDS
   return fwrite(&c, 1, 1, stream);
}
