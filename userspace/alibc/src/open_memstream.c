#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <syscall.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

FILE *open_memstream(char **ptr, size_t *sizeloc)
{
   FILE* ret = malloc(sizeof(FILE));
   initfile(ret);
   char name[64];
   sprintf(name, "%p-%ld", *ptr, sizeloc);
   ret->size = 0;
   ret->type = F_NAMEDMEM;
   ((amemfile*)ret)->membuf = asyscall(SYS_SHARED, "memfd", ret->file, "", &ret->size, 0, 0);
   *sizeloc = ret->size;
   ptr = malloc(1); /* Dummy for caller free */
   return ret;
}
