#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int fgetpwent_r(FILE * stream, struct passwd * pwbuf,
   char * buf, size_t buflen,
   struct passwd ** pwbufp)
{
   if (!fgets(buf, buflen, stream)) {
      *pwbufp = NULL;
      return ERANGE;
   }
   buf[strlen(buf) - 1] = '\0';
   pwbuf->pw_name = strtok(buf, ":");
   pwbuf->pw_passwd = strtok(NULL, ":");
   char* tok;
   if ((tok = strtok(NULL, ":")))  pwbuf->pw_uid = atoi(tok);
   else pwbuf->pw_uid = -1;
   if ((tok = strtok(NULL, ":")))  pwbuf->pw_gid = atoi(tok);
   else pwbuf->pw_gid = -1;
   pwbuf->pw_gecos = strtok(NULL, ":");
   pwbuf->pw_dir = strtok(NULL, ":");
   pwbuf->pw_shell = strtok(NULL, ":");
   *pwbufp = pwbuf;
   return 0;
}
