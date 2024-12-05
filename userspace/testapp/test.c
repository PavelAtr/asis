#include <stdio.h>
#include <pwd.h>


int main(int argc, char** argv)
{
	struct passwd p;
	FILE* dbpasswd = fopen("/etc/passwd", "r");
	fscanf(dbpasswd, "%s:%s:%d:%d:%s:%s:%s", p.pw_name, p.pw_passwd,
	        &p.pw_uid, &p.pw_gid, p.pw_gecos, p.pw_dir, p.pw_shell);
	size_t size = fprintf(stdout, "%s:%s:%d:%d:%s:%s:%s", p.pw_name, p.pw_passwd,
	    p.pw_uid, p.pw_gid, p.pw_gecos, p.pw_dir, p.pw_shell);

	return size;
}
