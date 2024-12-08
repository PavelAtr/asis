#include <stdio.h>

int putchar(int c)
{
  return fwrite(&c, 1, 1, stdout);
}
