#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

mode_t umask(mode_t mask)
{
   char envumask[16];
   sprintf(envumask, "0%o", mask);
   setenv("UMASK", envumask, 0);
   return mask;
}
