#include <asis.h>
#include "../config.h"
#include <syscall.h>

long64_t sys_syscall(int number, long64_t arg1, long64_t arg2, long64_t arg3, long64_t arg4, long64_t arg5, long64_t arg6)
{
   switch (number) {
   case SYS_MALLOC:
      return (addr_t)sys_malloc((size_t) arg1);
      break;
   case SYS_FREE:
      sys_free((void*) arg1);
      break;
   case SYS_MMAP:
      return (addr_t)sys_mmap((void*)arg1, (size_t)arg2, (int_t)arg3, (int_t)arg4, (int_t)arg5, (off_t)arg6);
      break;
   case SYS_MUNMAP:
      return sys_munmap((void*)arg1, (size_t)arg2);
      break;
   case SYS_FWRITE:
      return sys_afwrite( (char*)arg1, (void*)arg2, (size_t)arg3, (size_t)arg4);
      break;
   case SYS_FREAD:
      return sys_afread((char*)arg1, (void*)arg2, (size_t)arg3, (size_t)arg4);
      break;
   case SYS_FSTAT:
      return sys_stat((const char*)arg1, (void*)arg2);
      break;
   case SYS_DBG:
      sys_printf("%d %d %d %d %d %d\n", (int) arg1, (int) arg2, (int) arg3, (int) arg4, (int) arg5, (int) arg6);
      break;
   case SYS_USLEEP:
      return sys_usleep((long_t)arg1);
      break;
   case SYS_EXECVE:
      return sys_exec((char*)arg1, (char**)arg2, (char**)arg3);
      break;
   case SYS_READDIR:
      return (long_t)sys_readdir((char*)arg1, (int)arg2);
   case SYS_MKNOD:
      return sys_mknod((char*)arg1, (mode_t)arg2);
   case SYS_MODNOD:
      return sys_modnod((char*)arg1, (uid_t)arg2, (gid_t)arg3, (mode_t)arg4);
   case SYS_UNLINK:
      return sys_unlink((char*)arg1);
   case SYS_TRUNCATE:
      return sys_truncate((char*)arg1, (size_t)arg2);
   case SYS_LINK:
      return sys_link((char*)arg1, (char*)arg2, 0);
   case SYS_RENAME:
      return sys_link((char*)arg1, (char*)arg2, 1);
   case SYS_GETUID:
      return current->uid;
   case SYS_GETGID:
      return current->gid;
   case SYS_SETUID:
      return sys_setuid((uid_t)arg1);
   case SYS_SETGID:
      return sys_setgid((gid_t)arg1);
   case SYS_GETMAXFD:
      return COREMAXFD;
   case SYS_CLONE:
      return sys_clone();
   case SYS_FORK:
      return sys_fork();
   case SYS_WAITPID:
      return sys_waitpid((pid_t)arg1, (int*)arg2, (int)arg3);
   case SYS_REALLOC:
      return (addr_t)sys_realloc((void*)arg1, (size_t)arg2);
   case SYS_IOCTL:
      current->sys_errno = sys_ioctl((const char*)arg1, (ulong_t)arg2, (void*)arg3);
      if (current->sys_errno) {
         return -1;
      } else {
		 return 0;
	  }
   case SYS_GETPID:
      return current->pid;
   case SYS_GETPPID:
      return current->parentpid;
   case SYS_GETPGID:
      return sys_getpgid((int)arg1);
   case SYS_SETPGID:
      return sys_setpgid((pid_t)arg1, (pid_t)arg2);
   case SYS_SETJMP:
      return sys_setjmp((long_t*)arg1);
   case SYS_LONGJMP:
      return sys_longjmp((long_t*)arg1);
   case SYS_GETRLIMIT:
      return sys_getrlimit((int)arg1, (void*)arg2);
   case SYS_GETERRNO:
      return sys_geterrno();
   default:
      sys_printf(SYS_INFO "Unsupported syscall %d\n", number);
      break;
   }
   return 0;
}
