#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>

FILE* dbpasswd = NULL;

int main(int argc, char** argv)
{
   FILE* passdb = fopen("/etc/passwd", "r");
   char buf[4096];
   struct passwd* p;
   struct passwd in;
   while(!fgetpwent_r(passdb, &in,  buf, 4096, &p))
      fprintf(stdout, "%s:%s:%d:%d:%s:%s:%s\n", p->pw_name,
         p->pw_passwd, p->pw_uid, p->pw_gid, p->pw_gecos, p->pw_dir,
         p->pw_shell);

   fprintf(stdout, "ONCEMORE\n");
   setpwent();
   while ((p = getpwent()))
      fprintf(stdout, "%s:%s:%d:%d:%s:%s:%s\n", p->pw_name,
         p->pw_passwd, p->pw_uid, p->pw_gid, p->pw_gecos, p->pw_dir,
         p->pw_shell);
   endpwent();

   fprintf(stdout, "UID=1000\n");  
   setpwent();
   getpwuid_r(1000, &in, buf, 4096, &p);
   fprintf(stdout, "%s:%s:%d:%d:%s:%s:%s\n", p->pw_name,
         p->pw_passwd, p->pw_uid, p->pw_gid, p->pw_gecos, p->pw_dir,
         p->pw_shell);
   endpwent();

   fprintf(stdout, "NAME=bin\n");  
   setpwent();
   getpwnam_r("bin", &in, buf, 4096, &p);
   fprintf(stdout, "%s:%s:%d:%d:%s:%s:%s\n", p->pw_name,
         p->pw_passwd, p->pw_uid, p->pw_gid, p->pw_gecos, p->pw_dir,
         p->pw_shell);
   endpwent();

   fprintf(stdout, "ONCEMORE\n");

   fprintf(stdout, "UID=1000\n");  
   setpwent();
   p = getpwuid(1000);
   fprintf(stdout, "%s:%s:%d:%d:%s:%s:%s\n", p->pw_name,
         p->pw_passwd, p->pw_uid, p->pw_gid, p->pw_gecos, p->pw_dir,
         p->pw_shell);
   endpwent();

   fprintf(stdout, "NAME=bin\n");  
   setpwent();
   p = getpwnam("bin");
   fprintf(stdout, "%s:%s:%d:%d:%s:%s:%s\n", p->pw_name,
         p->pw_passwd, p->pw_uid, p->pw_gid, p->pw_gecos, p->pw_dir,
         p->pw_shell);
   endpwent();



   return 0;
}
