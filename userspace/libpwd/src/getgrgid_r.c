#include <grp.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int getgrgid_r(gid_t gid, struct group* grp,
               char* buf, size_t buflen, struct group** result)
{
   while (!fgetgrent_r(dbgroup, grp, buf, buflen, result)) {
      if ((*result)->gr_gid == gid) {
         return 0;
      }
      free((*result)->gr_mem);
   }
   *result = NULL;
   return ENOENT;
}
