#include <grp.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int getgrnam_r(const char* name, struct group* grp,
               char* buf, size_t buflen, struct group** result)
{
   while (!fgetgrent_r(dbgroup, grp, buf, buflen, result)) {
      if (strcmp((*result)->gr_name, name) == 0) {
         return 0;
      }
   }
   *result = NULL;
   return ENOENT;
}
