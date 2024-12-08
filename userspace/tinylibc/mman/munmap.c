#include <syscall.h>
#include <sys/types.h>

int munmap(void* addr, size_t length)
{
  syscall(SYS_MUNMAP, addr, length);
  return 0;
}
