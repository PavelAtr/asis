#ifndef _GRP_H
#define _GRP_H

#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MAXPWDLINE 1024
#define GROUP_FILE "/etc/group"

struct group {
  char   *gr_name;        /* group name */
  char   *gr_passwd;      /* group password */
  gid_t   gr_gid;         /* group ID */
  char  *gr_mem;         /* Not standard but simple */
};

extern FILE* dbgroup; /* Need stored in client application */

static inline void endgrent(void)
{
   if (dbgroup) {
      fclose(dbgroup);
      dbgroup = NULL;
   }
};

static inline void setgrent(void)
{
   endgrent();
   dbgroup = fopen(GROUP_FILE, "r");
};

static inline int setgroupent (int stayopen)
{
   setgrent();
   return 0;
};

int fgetgrent_r(FILE* stream, struct group* gbuf,
                char* buf, size_t buflen, struct group** gbufp);

static inline int getgrnam_r(const char* name, struct group* grp,
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

static inline int getgrgid_r(gid_t gid, struct group* grp,
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

static inline struct group *getgrent(void)
{
   char buf[MAXPWDLINE];
   struct group grp;
   struct group* g;
   if (!fgetgrent_r(dbgroup, &grp,  buf, MAXPWDLINE, &g)) {
      return g;
   }
   return NULL;
};

static inline struct group *getgrnam(const char *name)
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

static inline struct group *getgrgid(gid_t gid)
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

extern int initgroups(const char *user, gid_t group);

#endif
