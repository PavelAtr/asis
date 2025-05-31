#include <syscall.h>
#include <sys/types.h>

void* mmap(void* addr, size_t length, int prot, int flags,
   int fd, off_t offset)
{
   return (void*)asyscall(SYS_MMAP, addr, length, prot, flags, fd, offset >> 12);
}
