#include <stdio.h>
#include <stdio.h>
#include <pwd.h>

int main(int argc, char** argv)
{
   FILE* passdb = fopen("/tinysys/passwd", "r");
   fprintf(stdout, "size=%d\n", passdb->size);
   char buf[4096];
   struct passwd* p;
   struct passwd in;
   while(!fgetpwent_r(passdb, &in,  buf, 4096, &p))
      fprintf(stdout, "%s:%s:%d:%d:%s:%s:%s\n", p->pw_name,
         p->pw_passwd, p->pw_uid, p->pw_gid, p->pw_gecos, p->pw_dir,
         p->pw_shell);
   return 0;
}
