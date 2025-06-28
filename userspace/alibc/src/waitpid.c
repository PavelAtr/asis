#include <sys/types.h>
#include <syscall.h>
#include <errno.h>


pid_t waitpid(pid_t pid, int* wstatus, int options)
{
   pid_t ret = (pid_t)asyscall(SYS_WAITPID, pid, wstatus, options, 0, 0, 0);
   if (ret == (pid_t)-2) {
      // If no child process is found, return -1 and set errno to ECHILD
      errno = ECHILD;
      return -1;
   }
   return ret;
}

pid_t wait(int* wstatus)
{
   return waitpid(-1, wstatus, 0);
}