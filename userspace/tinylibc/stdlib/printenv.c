#include <stdlib.h>
#include <stdio.h>

extern char*** environ;

void printenv()
{
   int i;
   for(i = 0; (*environ)[i]; i++)
      if (((*environ)[i])[0] != '\0') {
         puts((*environ)[i]);
         puts("\n");
      }
}
