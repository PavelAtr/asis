#include <string.h>

char *basename(char *path)
{
  return strrchr(path, '/');
}
