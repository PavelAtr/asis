#include <stdio.h>
#include <stdio.h>
#include <pwd.h>

int main(int argc, char** argv)
{
   FILE* passwd = fopen("/etc/passwd", "r");
   char buf[1024];
   struct passwd* p;
   struct passwd in;
   while(!fgetpwent_r(passwd, &in,  buf, 1024, &p)) {
      fprintf(stdout, "%s:%s:%d:%d:%s:%s:%s\n", p->pw_name, p->pw_passwd, p->pw_uid,
         p->pw_gid, p->pw_gecos, p->pw_dir, p->pw_shell);
   }
   return 0;
}
