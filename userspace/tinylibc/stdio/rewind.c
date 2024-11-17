#include <stdio.h>

inline void rewind(FILE* stream)
{
	stream->pos = 0;
}
