#include <stdio.h>
#include <stdlib.h>

FILE *open_memstream(char **ptr, size_t *sizeloc)
{
   amemfile* ret = malloc(sizeof(amemfile));
   ret->type = F_MEM;
   initfile((FILE*)ret);
   ret->membuf = malloc(1);
   ret->size = 1;
   ret->clientptr = ptr;
   ret->clientsize = sizeloc;
   *ret->clientsize = ret->size;
   *ret->clientptr = ret->membuf;
   return (FILE*)ret;
}
