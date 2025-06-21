/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int vasprintf(char ** strp, const char * fmt, va_list ap)
{
   va_list copy;
   va_copy(copy, ap);
   size_t size = vsprintf(NULL, format, ap);
   char* str = malloc(size);
   size = vsprintf(str, format, copy);
   *strp = str;
   return size;
}


int asprintf(char **restrict strp, const char *restrict fmt, ...)
{
    va_list vl;
    va_start(vl, fmt);
    size_t size = vasprintf(strp, fmt, vl);
    return size;
}
