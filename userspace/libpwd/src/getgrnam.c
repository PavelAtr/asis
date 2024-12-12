#include <grp.h>
#include <stddef.h>

struct group *getgrnam(const char *name)
{
   if (!getgrnam_r(name, &grp, buf, MAXPWDLINE, &g)) {
      return g;
   }
   return NULL;

}
