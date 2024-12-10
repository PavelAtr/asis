#include <pwd.h>

void setpwent(void)
{
   endpwent();
   dbpasswd = fopen(PASSWD_FILE, "r");
}

void endpwent(void)
{
   if (dbpasswd) {
      fclose(dbpasswd);
      dbpasswd = NULL;
   }
}
