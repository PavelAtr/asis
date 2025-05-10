#include <stdlib.h>
#include <stdio.h>

void printenv()
{
   INIT_ENVIRON
   printf("environ=%p environ[0]=%p\n", environ, environ[0]);
   int i;
   for(i = 0; environ[i]; i++)
      if ((environ[i])[0] != '\0') {
         puts(environ[i]);
      }
}
