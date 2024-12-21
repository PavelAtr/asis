#include <time.h>

/* NOT REALIZED */

struct tm t2;

struct tm *localtime(const time_t *timep)
{
      return &t2;
}