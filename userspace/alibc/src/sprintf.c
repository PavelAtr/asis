/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <stdio.h>

int sprintf(char* str, const char* format, ...)
{
    va_list vl;
    va_start(vl, format);
    int n = snprintf(str, -1, format, vl);
    va_end(vl);
    return 0;
}



