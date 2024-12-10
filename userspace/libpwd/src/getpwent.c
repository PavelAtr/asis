#include <pwd.h>
#include <stddef.h>

struct passwd *getpwent(void)
{
   if (!fgetpwent_r(dbpasswd, &pass,  buf, MAXPWDLINE, &p)) {
      return p;
   }
   return NULL;
}
