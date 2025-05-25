#include <stdio.h>
#include <string.h>

int fputs(const char* s, FILE* stream)
{
INIT_FDS
   size_t len = fwrite(s, 1, strlen(s), stream);
   len += fwrite("\n", 1, 1, stream);
   return len;
}

int puts(const char* s)
{
INIT_FDS
   return fputs(s, stdout);
}
