#include <grp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
   FILE* groupdb = fopen("/etc/group", "r");
   char buf[4096];
   struct group* p;
   struct group in;
   while(!fgetgrent_r(groupdb, &in,  buf, 4096, &p)) {
      fprintf(stdout, "%s:%s:%d:%s\n", p->gr_name,
         p->gr_passwd, p->gr_gid, p->gr_mem);
   }
   fprintf(stdout, "ONCEMORE\n");
   setgrent();
   while ((p = getgrent())) {
      fprintf(stdout, "%s:%s:%d:%s\n", p->gr_name,
         p->gr_passwd, p->gr_gid, p->gr_mem);
   }
   endgrent();
   fprintf(stdout, "GID=1000\n");
   setgrent();
   getgrgid_r(1000, &in, buf, 4096, &p);
   fprintf(stdout, "%s:%s:%d:%s", p->gr_name,
      p->gr_passwd, p->gr_gid, p->gr_mem);
   endgrent();
   fprintf(stdout, "NAME=bin\n");
   setgrent();
   getgrnam_r("bin", &in, buf, 4096, &p);
   fprintf(stdout, "%s:%s:%d:%s\n", p->gr_name,
      p->gr_passwd, p->gr_gid, p->gr_mem);
   endgrent();
   fprintf(stdout, "ONCEMORE\n");
   fprintf(stdout, "GID=1000\n");
   setgrent();
   p = getgrgid(1000);
   fprintf(stdout, "%s:%s:%d:%s\n", p->gr_name,
      p->gr_passwd, p->gr_gid, p->gr_mem);
   endgrent();
   fprintf(stdout, "NAME=bin\n");
   setgrent();
   p = getgrnam("bin");
   fprintf(stdout, "%s:%s:%d:%s\n", p->gr_name,
      p->gr_passwd, p->gr_gid, p->gr_mem);
   endgrent();
   return 0;
}
