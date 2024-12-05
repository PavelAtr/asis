#include <stdio.h>
#include <stdarg.h>

char buf[MAXSTRING];

int fscanf(FILE* stream, const char* format, ...)
{
    va_list args;
    int n;

    va_start(args, format);
    n = vsscanf(fgets(buf, MAXSTRING, stream), format, args);
    va_end(args);

    return n;
}
