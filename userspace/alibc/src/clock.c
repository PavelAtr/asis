#include <time.h>

clock_t c = 0;

/* NOT REALIZED */
clock_t clock(void)
{
   return c++;
}