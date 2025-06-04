#include <grp.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int fgetgrent_r(FILE* stream, struct group* gbuf,
                 char* buf, size_t buflen,
                 struct group** gbufp)
{
   memset(buf, 0x0, buflen);
   memset(gbuf, 0x0, sizeof(struct group));
   if (!fgets(buf, buflen, stream)) {
      *gbufp = NULL;
      return ERANGE;
   }
   buf[strlen(buf) - 1] = '\0';
   gbuf->gr_name = strtok(buf, ":");
   gbuf->gr_passwd = strtok(NULL, ":");
   char* tok;
   if ((tok = strtok(NULL, ":")))
       gbuf->gr_gid = atoi(tok);
   gbuf->gr_mem = strtok(NULL, ":");
   *gbufp = gbuf;
   return 0;
}
