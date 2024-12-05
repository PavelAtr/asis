#include <pwd.h>

FILE* dbpasswd = NULL;

void setpwent(void)
{
    if (dbpasswd)
	fclose(dbpasswd);
    dbpasswd = fopen(PASSWD_FILE, "r");
}

void endpwent(void)
{
    if (dbpasswd)
	fclose(dbpasswd);
}
