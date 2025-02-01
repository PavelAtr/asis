#include <stdio.h>

inline void rewind(FILE* stream)
{
INIT_FDS
   stream->pos = 0;
}
