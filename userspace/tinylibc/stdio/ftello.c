#include <stdio.h>

off_t ftello(FILE *stream)
{
   return stream->pos;
}
