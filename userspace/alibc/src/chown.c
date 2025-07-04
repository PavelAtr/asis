#include <syscall.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stddef.h>
#include <errno.h>

int chown(const char *pathname, uid_t owner, gid_t group)
{
   struct stat st;
   stat(pathname, &st);
   if ((errno = (int)asyscall(SYS_MODNOD, pathname, owner, group, st.st_mode, 0, 0))) {
      return -1;
   }
   return 0;
}


/* NOT REALIZED */
int lchown(const char *pathname, uid_t owner, gid_t group)
{
   return 0;
}
