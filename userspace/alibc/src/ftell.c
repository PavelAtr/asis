#include <stdio.h>

long ftell(FILE* stream)
{
INIT_afds
   return stream->pos;
}
