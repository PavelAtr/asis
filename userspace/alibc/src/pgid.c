#include <unistd.h>
#include <syscall.h>

int setpgid(pid_t pid, pid_t pgid)
{
   return (int)asyscall(SYS_SETPGID, pid, pgid, 0, 0, 0, 0);
}

pid_t getpgid(pid_t pid)
{
   return (int)asyscall(SYS_GETPGID, pid, 0, 0, 0, 0, 0);
}

pid_t getpgrp(void)
{
   return getpgid(0);
}