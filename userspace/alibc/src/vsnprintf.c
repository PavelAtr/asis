#include <stdio.h>
#include <stdarg.h>

int vsnprintf(char str[], size_t size, const char* format, va_list ap)
{
   if (!str) return MAXSTRING;
   int n = vsprintf(str, format, ap);
   return n;
}
