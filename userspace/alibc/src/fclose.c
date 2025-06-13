#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fclose(FILE *stream)
{
INIT_afds
   if (stream->fd != -1) {
       return 0;
   }
   freefile(stream);
   return 0;
}
