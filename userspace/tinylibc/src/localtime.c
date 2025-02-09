#include <time.h>

/* NOT REALIZED */

struct tm t2;
struct tm *localtime(const time_t *timep)
{
   return &t2;
}

struct tm *localtime_r(const time_t* timep,
       struct tm* result)
{
   return  result;
}
