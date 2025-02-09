#include <stdio.h>
#include <string.h>

int fputs(const char* s, FILE* stream)
{
INIT_FDS
   return fwrite(s, strlen(s), 1, stream);
}

int puts(const char* s)
{
INIT_FDS
   return fputs(s, stdout);
}
