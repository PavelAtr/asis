#include <syscall.h>
#include <sys/types.h>

pid_t vfork(void)
{
    return syscall(SYS_FORK);
}