#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <syscall.h>
#include <errno.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

FILE *fmemopen(void* buf, size_t size, const char *mode)
{
   FILE* ret = malloc(sizeof(FILE));
   initfile(ret);
   ret->file = strdup("mem");
   ret->size = size;
   ret->strbuf = buf;
   return ret;
}
