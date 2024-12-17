#include <stdio.h>
#include <stdarg.h>

int printf(const char* format, ...)
{
   va_list args;
   int n;
   va_start(args, format);
   n = vfprintf(stdout, format, args);
   va_end(args);
   return n;
}
