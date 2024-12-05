#ifndef _PWD_H
#define _PWD_H

#include <sys/types.h>
#include <stdio.h>

#define PASSWD_FILE "/etc/passwd"

struct passwd {
   char   *pw_name;       /* username */
   char   *pw_passwd;     /* user password */
   uid_t   pw_uid;        /* user ID */
   gid_t   pw_gid;        /* group ID */
   char   *pw_gecos;      /* user information */
   char   *pw_dir;        /* home directory */
   char   *pw_shell;      /* shell program */
};

extern FILE* dbpasswd;

struct passwd *getpwent(void);
void setpwent(void);
void endpwent(void);

#endif