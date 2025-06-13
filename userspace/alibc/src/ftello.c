#include <stdio.h>

off_t ftello(FILE *stream)
{
INIT_afds
   return stream->pos;
}
