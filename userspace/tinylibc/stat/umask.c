#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

mode_t umask(mode_t newmask)
{
   char envumask[16];
   mode_t oldmask = 0000;
   if (getenv("UMASK")) {
      oldmask = mask;
   }
   sprintf(envumask, "0%o", newmask);
   setenv("UMASK", envumask, 0);
   return oldmask;
}
