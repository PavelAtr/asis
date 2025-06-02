#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void error(int status, int errnum, const char *format, ...)
{
    va_list vl;
    va_start(vl, format);
    char* message = strerror(errnum);
    const char* progname = getprogname();
    fprintf(stderr, "%s: %s ", progname, message);
    vfprintf(stderr, format, vl);
    _exit(status);
}