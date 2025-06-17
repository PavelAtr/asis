/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <stdio.h>

int vsprintf(char* str, const char* format, va_list ap)
{
    return vsnprintf(str, -1,  format, ap);
}



