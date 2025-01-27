#include <stdio.h>
#include <sys/types.h>

ssize_t getdelim(char** lineptr, size_t* n, int delim, FILE* stream)
{
   int i;
   int c;
   char* s = *lineptr;
   if (!s) {
      s = malloc(MAXSTRING);
   }
   for (i = 0; i < MAXSTRING - 1; i++) {
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
