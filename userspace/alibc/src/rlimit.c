#include <sys/resource.h>
#include <syscall.h>


int getrlimit(int resource, struct rlimit *rlim)
{
   return asyscall(SYS_GETRLIMIT, resource, rlim, 0, 0, 0, 0);
}

/* NOT REALIZED */

int setrlimit(int resource, const struct rlimit *rlim)
{
   return 0;
}