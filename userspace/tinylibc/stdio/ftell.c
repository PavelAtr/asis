#include <stdio.h>

long ftell(FILE* stream)
{
INIT_FDS
   return stream->pos;
}
