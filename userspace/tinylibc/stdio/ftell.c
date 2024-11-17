#include <stdio.h>

inline long ftell(FILE* stream)
{
	return stream->pos;
}
