#include <syscall.h>
#include <sys/types.h>

int setuid(uid_t uid)
{
    return syscall(SYS_SETUID, uid);
}

int setgid(gid_t gid)
{
    return syscall(SYS_SETGID, gid);
}

uid_t getuid(void)
{
    return syscall(SYS_GETUID);
}

gid_t getgid(void)
{
    return syscall(SYS_GETGID);
}
