#include <stdio.h>

char *fgets(char* s, int size, FILE* stream)
{
   int i;
   int c;
   for (i = 0; i < size - 1; i++) {
      c = getc(stream);
      s[i] = c;
      if (c == '\n') {
         break;
      }
      if (feof(stream)) {
         return NULL;
      }
   }
   s[i + 1] = '\0';
   return s;
}
