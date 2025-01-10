#ifndef _PWD_H
#define _PWD_H

#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

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

FILE* dbpasswd = NULL;

int fgetpwent_r(FILE * stream, struct passwd * pwbuf,
                char * buf, size_t buflen,
                struct passwd ** pwbufp);

inline int getpwnam_r(const char* name, struct passwd* pwd,
   char* buf, size_t buflen,
   struct passwd** pwbufp)
{
   while (!fgetpwent_r(dbpasswd, pwd, buf, buflen, pwbufp)) {
      if (strcmp((*pwbufp)->pw_name, name) == 0) {
         return 0;
      }
   }
   *pwbufp = NULL;
   return ENOENT;
}

inline int getpwuid_r(uid_t uid, struct passwd* pwd,
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

inline struct passwd *getpwent(void)
{
   char buf[MAXPWDLINE];
   struct passwd pass;
   struct passwd* p;
   if (!fgetpwent_r(dbpasswd, &pass,  buf, MAXPWDLINE, &p)) {
      return p;
   }
   return NULL;
}

inline struct passwd *getpwnam(const char *name)
{
   char buf[MAXPWDLINE];
   struct passwd pass;
   struct passwd* p;
   if (!getpwnam_r(name, &pass, buf, MAXPWDLINE, &p)) {
      return p;
   }
   return NULL;
}

inline struct passwd *getpwuid(uid_t uid)
{
   char buf[MAXPWDLINE];
   struct passwd pass;
   struct passwd* p;
   if (!getpwuid_r(uid, &pass, buf, MAXPWDLINE, &p)) {
      return p;
   }
   return NULL;
}

inline void endpwent(void)
{
   if (dbpasswd) {
      fclose(dbpasswd);
      dbpasswd = NULL;
   }
}

inline void setpwent(void)
{
   endpwent();
   dbpasswd = fopen(PASSWD_FILE, "r");
}

inline int setpassent (int stayopen)
{
   setpwent();
   return 0;
}

#endif
