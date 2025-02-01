#include <stdio.h>

off_t ftello(FILE *stream)
{
INIT_FDS
   return stream->pos;
}
