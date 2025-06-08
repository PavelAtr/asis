#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

__thread FILE* dbpasswd = NULL;

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

void endpwent(void)
{
   if (dbpasswd) {
      fclose(dbpasswd);
      dbpasswd = NULL;
   }
};

void setpwent(void)
{
   endpwent();
   dbpasswd = fopen(PASSWD_FILE, "r");
};

int setpassent (int stayopen)
{
   setpwent();
   return 0;
};

int getpwnam_r(const char* name, struct passwd* pwd,
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
};

int getpwuid_r(uid_t uid, struct passwd* pwd,
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
};

struct passwd *getpwent(void)
{
   char buf[MAXPWDLINE];
   struct passwd pass;
   struct passwd* p;
   if (!fgetpwent_r(dbpasswd, &pass,  buf, MAXPWDLINE, &p)) {
      return p;
   }
   return NULL;
};

struct passwd *getpwnam(const char *name)
{
   char buf[MAXPWDLINE];
   struct passwd pass;
   struct passwd* p;
   setpwent();
   if (!getpwnam_r(name, &pass, buf, MAXPWDLINE, &p)) {
      return p;
   }
   endpwent();
   return NULL;
};

struct passwd *getpwuid(uid_t uid)
{
   char buf[MAXPWDLINE];
   struct passwd pass;
   struct passwd* p;
   setpwent();
   if (!getpwuid_r(uid, &pass, buf, MAXPWDLINE, &p)) {
      return p;
   }
   endpwent();
   return NULL;
};
