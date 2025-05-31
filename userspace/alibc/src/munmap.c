#include <syscall.h>
#include <sys/types.h>

int munmap(void* addr, size_t length)
{
   asyscall(SYS_MUNMAP, addr, length, 0, 0, 0, 0);
   return 0;
}
