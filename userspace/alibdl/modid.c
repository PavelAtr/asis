#include "modid.h"

unsigned int store[MAXOBJECTS];

int get_modid()
{
    unsigned int i;
    for (i = 0; i < MAXOBJECTS; i++)
    if (!store[i]) {
	store[i] = 1;
	return i;
    }
    return -1;
}

void unget_modid(unsigned int ind)
{
    store[ind] = 0;
}
