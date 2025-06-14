#ifndef _GRP_H
#define _GRP_H

#include <sys/types.h>
#include <stdio.h>

#define MAXPWDLINE 1024
#define GROUP_FILE "/etc/group"

struct group {
  char   *gr_name;        /* group name */
  char   *gr_passwd;      /* group password */
  gid_t   gr_gid;         /* group ID */
  char  *gr_mem;         /* Not standard but simple */
};

extern __thread FILE* dbgroup; /* Need stored in client application */

void endgrent(void);
void setgrent(void);
int setgroupent (int stayopen);
int fgetgrent_r(FILE* stream, struct group* gbuf,
                char* buf, size_t buflen, struct group** gbufp);
int getgrnam_r(const char* name, struct group* grp,
               char* buf, size_t buflen, struct group** result);
int getgrgid_r(gid_t gid, struct group* grp,
               char* buf, size_t buflen, struct group** result);
struct group *getgrent(void);
struct group *getgrnam(const char *name);
struct group *getgrgid(gid_t gid);
extern int initgroups(const char *user, gid_t group);

#endif
