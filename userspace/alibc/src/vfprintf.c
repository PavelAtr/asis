/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int vfprintf(FILE* stream, const char* format, va_list ap)
{
INIT_afds
   va_list copy;
   va_copy(copy, ap);
   size_t size = vsprintf(NULL, format, ap);
   char* str = alloca(size);
   size = vsprintf(str, format, copy);
   size_t ret =  fwrite(str, 1, size, stream);
   return ret;
}
