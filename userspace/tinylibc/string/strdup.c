#include <string.h>
#include <stdlib.h>

char *strdup(const char *s)
{
  char* ret = malloc(strlen(s) + 1);
  strcpy(ret, s);
  return ret;
}