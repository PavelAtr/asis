#include <syscall.h>
#include <sys/types.h>

int setuid(uid_t uid)
{
   return (int)asyscall(SYS_SETUID, uid, 0, 0, 0, 0, 0);
}

int setgid(gid_t gid)
{
   return (int)asyscall(SYS_SETGID, gid, 0, 0, 0, 0, 0);
}

uid_t getuid(void)
{
   return (uid_t)asyscall(SYS_GETUID, 0, 0, 0, 0, 0, 0);
}

gid_t getgid(void)
{
   return (gid_t)asyscall(SYS_GETGID, 0, 0, 0, 0, 0, 0);
}
