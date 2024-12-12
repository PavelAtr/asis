#include <grp.h>
#include <stddef.h>

struct group *getgrgid(gid_t gid)
{
   if (!getgrgid_r(gid, &grp, buf, MAXPWDLINE, &g)) {
      return g;
   }
   return NULL;

}
