#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

char str[MAXSTRING];
int vfprintf(FILE* stream, const char* format, va_list ap)
{
INIT_afds
   size_t size = vsprintf(str, format, ap);
   size_t ret =  fwrite(str, 1, size, stream);
   return ret;
}
