#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

ssize_t getdelim(char** lineptr, size_t* n, int delim, FILE* stream)
{
INIT_FDS
   int i;
   int c;
   char* s = *lineptr;
   size_t maxlen = (*n < MAXGETLINE)? *n : MAXGETLINE;
   if (!s) {
      s = malloc(maxlen);
   }
   for (i = 0; i < maxlen - 1; i++) {
      c = getc(stream);
      s[i] = c;
      if (c == delim || feof(stream)) {
         break;
      }
   }
   s[i] = '\0';
   *lineptr = s;
   if (i == 0) {
      return -1;
   }
   return i;
}
