#include <syscall.h>
#include <sys/types.h>

int setuid(uid_t uid)
{
   return asyscall(SYS_SETUID, uid, 0, 0, 0, 0, 0);
}

int setgid(gid_t gid)
{
   return asyscall(SYS_SETGID, gid, 0, 0, 0, 0, 0);
}

uid_t getuid(void)
{
   return asyscall(SYS_GETUID, 0, 0, 0, 0, 0, 0);
}

gid_t getgid(void)
{
   return asyscall(SYS_GETGID, 0, 0, 0, 0, 0, 0);
}
