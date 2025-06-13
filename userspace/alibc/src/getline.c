#include <stdio.h>
#include <sys/types.h>

ssize_t getline(char** lineptr, size_t* n, FILE* stream)
{
INIT_afds
   return getdelim(lineptr, n, '\n', stream);
}
