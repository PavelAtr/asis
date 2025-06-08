#ifndef _PWD_H
#define _PWD_H

#include <sys/types.h>
#include <stdio.h>

#define MAXPWDLINE 1024
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

extern __thread FILE* dbpasswd; /* Need stored in client application */

int fgetpwent_r(FILE * stream, struct passwd * pwbuf,
                char * buf, size_t buflen,
                struct passwd ** pwbufp);


void endpwent(void);
void setpwent(void);
int setpassent (int stayopen);
int getpwnam_r(const char* name, struct passwd* pwd,
   char* buf, size_t buflen,
   struct passwd** pwbufp);
int getpwuid_r(uid_t uid, struct passwd* pwd,
   char* buf, size_t buflen,
   struct passwd** pwbufp);
struct passwd *getpwent(void);
struct passwd *getpwnam(const char *name);
struct passwd *getpwuid(uid_t uid);

#endif
