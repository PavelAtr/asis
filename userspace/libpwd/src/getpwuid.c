#include <pwd.h>
#include <stddef.h>

struct passwd *getpwuid(uid_t uid)
{
   if (!getpwuid_r(uid, &pass, buf, MAXPWDLINE, &p)) {
      return p;
   }
   return NULL;

}
