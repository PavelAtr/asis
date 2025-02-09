#include <stdio.h>

int putchar(int c)
{
INIT_FDS
   return fwrite(&c, 1, 1, stdout);
}
