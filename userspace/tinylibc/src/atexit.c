#include <stdlib.h>

void (*atexit_func)(void) = NULL;

int atexit(void (*function)(void))
{
   atexit_func = function;
   return 0;
}