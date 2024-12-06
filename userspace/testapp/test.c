#include <stdio.h>
#include <pwd.h>
#include <string.h>

int main(int argc, char** argv)
{
	struct passwd p;
	FILE* dbpasswd = fopen("/etc/passwd", "r");
	char str[4096];
	char pw_name[256];
	char pw_passwd[256];
	uid_t pw_uid;
	gid_t pw_gid;
	char pw_gecos[256];
	char pw_dir[256];
        char pw_shell[256];
	if (!dbpasswd)
	{
	    fprintf(stderr, "Error open databse!\n");
	    return 1;
	}
	int ret;
	while (1)
	{
	    if ((ret = fscanf(dbpasswd, "%s:%s:%d:%d:%s:%s:%s\n", pw_name, pw_passwd,
	        &pw_uid, &pw_gid, pw_gecos, pw_dir, pw_shell)) == EOF) break;
	    fprintf(stdout, "%s:%s:%d:%d:%s:%s:%s\n", pw_name, pw_passwd,
		pw_uid, pw_gid, pw_gecos, pw_dir, pw_shell);
	}

	fclose(dbpasswd);

	return ret;
}
