#include <stdio.h>

inline void rewind(FILE* stream)
{
INIT_afds
   stream->pos = 0;
}
