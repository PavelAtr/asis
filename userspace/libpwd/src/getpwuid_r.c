#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int getpwuid_r(uid_t uid, struct passwd* pwd,
   char* buf, size_t buflen,
   struct passwd** pwbufp)
{
   while (!fgetpwent_r(dbpasswd, pwd, buf, buflen, pwbufp)) {
      if ((*pwbufp)->pw_uid == uid) {
         return 0;
      }
   }
   *pwbufp = NULL;
   return ENOENT;
}
