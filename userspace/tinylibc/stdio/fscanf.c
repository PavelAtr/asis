#include <stdio.h>
#include <stdarg.h>

char buf[MAXSTRING];

int fscanf(FILE* stream, const char* format, ...)
{
    va_list args;
    int n;

    va_start(args, format);
    fgets(buf, MAXSTRING, stream);
    if (buf[0] = '\0') return EOF;
    n = vsscanf(buf, format, args);
    va_end(args);

    return n;
}
