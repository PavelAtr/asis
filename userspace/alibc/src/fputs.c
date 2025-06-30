#include <stdio.h>
#include <string.h>

int fputs(const char* s, FILE* stream)
{
   size_t len = fwrite(s, 1, strlen(s), stream);
   return len;
}

int puts(const char* s)
{
   return fputs(s, stdout);
}
