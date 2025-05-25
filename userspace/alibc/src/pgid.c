#include <unistd.h>
#include <syscall.h>

int setpgid(pid_t pid, pid_t pgid)
{
   return syscall(SYS_SETPGID, pid, pgid);
}

pid_t getpgid(pid_t pid)
{
   return syscall(SYS_GETPGID, pid);
}

pid_t getpgrp(void)
{
   return getpgid(0);
}