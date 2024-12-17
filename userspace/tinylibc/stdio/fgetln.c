#include <stdio.h>

char s[MAXGETLINE];

char * fgetln (FILE *stream, size_t *len)
{
   int i;
   int c;
   for (i = 0; i < MAXSTRING - 1; i++) {
      c = getc(stream);
      s[i] = c;
      if (c == '\n') {
         break;
      }
      if (feof(stream)) {
         return NULL;
      }
   }
   *len = i;
   return s;
}
