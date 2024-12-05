#include <stdio.h>
#include <stdarg.h>

int sscanf(const char* str, const char* format, ...)
{
    va_list args;
    int n;

    va_start(args, format);
    n = vsscanf(str, format, args);
    va_end(args);

    return n;
}
