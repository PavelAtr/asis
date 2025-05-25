#include <sys/resource.h>
#include <syscall.h>


int getrlimit(int resource, struct rlimit *rlim)
{
   return syscall(SYS_GETRLIMIT, resource, rlim);
}

/* NOT REALIZED */

int setrlimit(int resource, const struct rlimit *rlim)
{
   return 0;
}