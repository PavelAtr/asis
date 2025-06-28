#include <stdlib.h>
#include <stdio.h>

void printenv()
{
   INIT_ENVIRON;
   if (!environ) {
      printf("Environment is not initialized.\n");
      return;
   }
   int i;
   printf("Environ=%p\n", environ);
   for (i = 0; environ[i]; i++) {
         printf("%s\n", environ[i]);
   }
}
