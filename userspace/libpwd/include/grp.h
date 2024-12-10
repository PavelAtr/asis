#ifndef _PWD_H
#define _PWD_H

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

#endif
