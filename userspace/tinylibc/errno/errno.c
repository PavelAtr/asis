#include <errno.h>
#include <syscall.h>

int get_errno()
{
  return syscall(SYS_GETERRNO);
}

int set_errno(int err)
{
  return syscall(SYS_SETERRNO, err);
}
