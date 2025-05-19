#ifdef UEFI
#include "uefi/uefi.h"
#else
#include <stdio.h>
#include <stdarg.h>
#endif

#define MAXLOG 1024

char tinylog[MAXLOG];

int sys_printf(const char* format, ...)
{
   va_list vl;
   va_start(vl, format);
   int ret = vsnprintf(tinylog, MAXLOG, format, vl);
#ifndef UEFI
   fprintf(stderr, "%s", tinylog);
#else
   printf("%s", tinylog);
#endif
   return ret;
}
