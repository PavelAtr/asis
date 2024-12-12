#include <grp.h>
#include <stddef.h>

struct group *getgrent(void)
{
   if (!fgetgrent_r(dbgroup, &grp,  buf, MAXPWDLINE, &g)) {
      return g;
   }
   return NULL;
}
