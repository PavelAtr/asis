#include <stdio.h>

int fputc(int c, FILE *stream)
{
INIT_afds
   return fwrite(&c, 1, 1, stream);
}
