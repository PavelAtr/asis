#include <stdio.h>

char *fgets(char* s, int size, FILE* stream)
{
INIT_FDS
   int i;
   int c;
   for (i = 0; i < size - 1; i++) {
      c = getc(stream);
      s[i] = c;
      if (c == '\n') {
         break;
      }
      if (c == EOF) {
         if (i) i--;
         break;
      }
      if (feof(stream)) {
         return NULL;
      }
   }
   s[i + 1] = '\0';
   if (s[0] == '\0' || s[0] == EOF) return NULL;
   return s;
}
