#include <time.h>
#include <string.h>

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

char *asctime(const struct tm *tm)
{
  return "asctime";
}

char *asctime_r(const struct tm * tm, char buf[])
{
  memcpy(buf, "asctime_r", 10);
  return buf;
}

char *ctime(const time_t *timep)
{
  return "ctime";
}

char *ctime_r(const time_t * timep,char buf[]) {
  memcpy(buf, "ctime_r", 8);
  return buf;
}

struct tm *gmtime(const time_t *timep)
{
  return &t2;
}

struct tm *gmtime_r(const time_t * timep, struct tm * result)
{
  return result;
}
