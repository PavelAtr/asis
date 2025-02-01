#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int vfprintf(FILE* stream, const char* format, va_list ap)
{
INIT_FDS
   va_list ap2;
   va_copy(ap2, ap);
   int size = vsnprintf(NULL, MAXSTRING, format, ap);
   char* str = malloc(size + 1);
   size = vsnprintf(str, MAXSTRING, format, ap2);
   size_t ret =  fwrite(str, 1, size, stream);
   free(str);
   return ret;
}
