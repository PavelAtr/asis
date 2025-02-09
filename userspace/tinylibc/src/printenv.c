#include <stdlib.h>
#include <stdio.h>

void printenv()
{
   INIT_ENVIRON
   int i;
   for(i = 0; environ[i]; i++)
      if ((environ[i])[0] != '\0') {
         puts(environ[i]);
         puts("\n");
      }
}
