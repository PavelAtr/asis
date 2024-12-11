#include <pwd.h>

int setpassent (int stayopen)
{
   setpwent();
   return 0;
}