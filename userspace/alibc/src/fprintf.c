#include <stdio.h>
#include <stdarg.h>

int fprintf(FILE* stream, const char* format, ...)
{
INIT_afds
   va_list args;
   int n;
   va_start(args, format);
   n = vfprintf(stream, format, args);
   va_end(args);
   return n;
}
