#include <syscall.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stddef.h>

int chown(const char *pathname, uid_t owner, gid_t group)
{
   struct stat st;
   stat(pathname, &st);
   return (int)asyscall(SYS_MODNOD, pathname, NULL, owner, group, st.st_mode, 0);
}


/* NOT REALIZED */
int lchown(const char *pathname, uid_t owner, gid_t group)
{
   return 0;
}
