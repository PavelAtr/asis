#include <stdlib.h>
#include <stdio.h>

void printenv()
{
   if (!environ) {
      printf("Environment is not initialized.\n");
      return;
   }
   int i;
   for (i = 0; environ[i]; i++) {
         printf("%s\n", environ[i]);
   }
}
