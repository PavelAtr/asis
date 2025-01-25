#include <stdlib.h>

int atexit(void (*function)(void))
{
   atexit_func = function;
   return 0;
}