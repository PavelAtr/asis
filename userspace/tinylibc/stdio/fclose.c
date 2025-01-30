#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int fclose(FILE *stream)
{
   freefile(stream);
   stream = NULL;
   return 0;
}
