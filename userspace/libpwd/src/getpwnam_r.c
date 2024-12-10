#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int getpwnam_r(const char* name, struct passwd* pwd,
   char* buf, size_t buflen,
   struct passwd** pwbufp)
{
   while (!fgetpwent_r(dbpasswd, pwd, buf, buflen, pwbufp)) {
      if (strcmp((*pwbufp)->pw_name, name) == 0) {
         return 0;
      }
   }
   *pwbufp = NULL;
   return ENOENT;
}
