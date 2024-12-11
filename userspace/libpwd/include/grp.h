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
  char  **gr_mem;         /* NULL-terminated array of pointers
                              to names of group members */
};

extern char buf[MAXPWDLINE];
extern FILE* dbgroup;
extern struct group grp;

void setgrent(void);
void endgrent(void);
int fgetgrent_r(FILE* stream, struct group* gbuf,
                 char* buf, size_t buflen,
                 struct group** gbufp);
#endif
