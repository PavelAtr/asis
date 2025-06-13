#include <stdio.h>

int putchar(int c)
{
INIT_afds
   return fwrite(&c, 1, 1, stdout);
}
