#include "../config.h"
#include "./include/asis.h"

#undef printf

#ifdef CONFIG_UEFI
#include "uefi/uefi.h"
#endif

#ifdef CONFIG_LINUX
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
   if (LOG) {
      //fwrite(tinylog, 1, ret, (FILE*)LOG);
      fwrite(tinylog, 1, ret, stderr);
      fflush((FILE*)LOG);
   }
   return ret;
}

