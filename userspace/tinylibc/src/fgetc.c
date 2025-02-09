#include <stdio.h>
#include <unistd.h>

int fgetc(FILE* stream)
{
INIT_FDS
   char ret;
   size_t len = fread(&ret, 1, 1, stream);
   if (len == 0) {
      return EOF;
   }
   return ret;
}
