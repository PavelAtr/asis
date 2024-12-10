#include <pwd.h>
#include <stddef.h>

struct passwd *getpwnam(const char *name)
{
   if (!getpwnam_r(name, &pass, buf, MAXPWDLINE, &p)) {
      return p;
   }
   return NULL;

}
