#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <syscall.h>
#include <errno.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

char* tmpbuf;
size_t tmpsize;

FILE *fmemopen(void* buf, size_t size, const char *mode)
{
   FILE* ret = malloc(sizeof(amemfile));
   ret->type = F_MEM;
   initfile(ret);
   ret->size = size;
   ret->mode = mode;
   ((amemfile*)ret)->clientptr = &tmpbuf;
   ((amemfile*)ret)->clientsize = &size;
   ((amemfile*)ret)->membuf = buf;
   return ret;
}
