#include <stdio.h>
#include <stdarg.h>

int snprintf(char* s, size_t size, const char* format, ...)
{
   va_list args;
   int n;
   va_start(args, format);
   n = vsprintf(s, format, args);
   va_end(args);
   return n;
}
