#include <grp.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

__thread FILE* dbgroup = NULL;

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
   else 
       gbuf->gr_gid = -1;
   gbuf->gr_mem = strtok(NULL, ":");
   *gbufp = gbuf;
   return 0;
}

void endgrent(void)
{
   if (dbgroup) {
      fclose(dbgroup);
      dbgroup = NULL;
   }
};

void setgrent(void)
{
   endgrent();
   dbgroup = fopen(GROUP_FILE, "r");
};

int setgroupent (int stayopen)
{
   setgrent();
   return 0;
};

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
};

int getgrgid_r(gid_t gid, struct group* grp,
               char* buf, size_t buflen, struct group** result)
{
   while (!fgetgrent_r(dbgroup, grp, buf, buflen, result)) {
      if ((*result)->gr_gid == gid) {
         return 0;
      }
   }
   *result = NULL;
   return ENOENT;
};

struct group *getgrent(void)
{
   char buf[MAXPWDLINE];
   struct group grp;
   struct group* g;
   if (!fgetgrent_r(dbgroup, &grp,  buf, MAXPWDLINE, &g)) {
      return g;
   }
   return NULL;
};

struct group *getgrnam(const char *name)
{
   char buf[MAXPWDLINE];
   struct group grp;
   struct group* g;
   setgrent();
   if (!getgrnam_r(name, &grp, buf, MAXPWDLINE, &g)) {
      return g;
   }
   endgrent();
   return NULL;
};

struct group *getgrgid(gid_t gid)
{
   char buf[MAXPWDLINE];
   struct group grp;
   struct group* g;
   setgrent();
   if (!getgrgid_r(gid, &grp, buf, MAXPWDLINE, &g)) {
      return g;
   }
   endgrent();
   return NULL;
};
