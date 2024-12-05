#include <pwd.h>
#include <stdio.h>

struct passwd p;

struct passwd *getpwent(void)
{
    if (fscanf(dbpasswd, "%s:%s:%d:%d:%s:%s:%s", p.pw_name, p.pw_passwd,
			&p.pw_uid, &p.pw_gid, p.pw_gecos, p.pw_dir, p.pw_shell) == EOF);
		return NULL;
	return &p;
}

