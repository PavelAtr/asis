#include <grp.h>

int setgroupent (int stayopen)
{
   setgrent();
   return 0;
}