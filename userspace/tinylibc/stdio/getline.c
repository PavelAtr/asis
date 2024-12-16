#include <stdio.h>
#include <sys/types.h>

ssize_t getline(char** lineptr, size_t* n, FILE* stream)
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
         lineptr = NULL;
         return 0;
      }
   }
   s[i] = '\0';
   *n = i;
   lineptr = (char**)&s;
   return i;
}
