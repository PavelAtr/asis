#include <pwd.h>

void setpwent(void)
{
   fprintf(stdout, "SETPWENT\n");
   endpwent();
   dbpasswd = fopen(PASSWD_FILE, "r");
}

void endpwent(void)
{
  fprintf(stdout, "ENDPWENT\n");
   if (dbpasswd) {
      fclose(dbpasswd);
      dbpasswd = NULL;
   }
}
