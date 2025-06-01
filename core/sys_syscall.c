#include "../config.h"
#include <asis.h>
#include "../config.h"
#include <syscall.h>

#ifdef CONFIG_LINUX
#include <stddef.h>
#endif

void* sys_syscall(int number, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6)
{
   switch (number) {
   case SYS_MALLOC:
      return sys_malloc((size_t) arg1);
      break;
   case SYS_FREE:
      sys_free((void*) arg1);
      break;
   case SYS_MMAP:
      return sys_mmap((void*)arg1, (size_t)arg2, (int_t)arg3, (int_t)arg4, (int_t)arg5, (off_t)arg6);
      break;
   case SYS_MUNMAP:
      return (void*)sys_munmap((void*)arg1, (size_t)arg2);
      break;
   case SYS_FWRITE:
      return (void*)sys_afwrite( (char*)arg1, (void*)arg2, (size_t)arg3, (size_t)arg4);
      break;
   case SYS_FREAD:
      return (void*)sys_afread((char*)arg1, (void*)arg2, (size_t)arg3, (size_t)arg4);
      break;
   case SYS_FSTAT:
      return (void*)sys_stat((const char*)arg1, (void*)arg2);
      break;
   case SYS_DBG:
      sys_printf("%d %d %d %d %d %d\n", (int) arg1, (int) arg2, (int) arg3, (int) arg4, (int) arg5, (int) arg6);
      break;
   case SYS_USLEEP:
      return (void*)sys_usleep((long_t)arg1);
      break;
   case SYS_EXECVE:
      return (void*)sys_exec((char*)arg1, (char**)arg2, (char**)arg3);
      break;
   case SYS_READDIR:
      return sys_readdir((char*)arg1, (int)arg2);
   case SYS_MKNOD:
      return (void*)sys_mknod((char*)arg1, (mode_t)arg2);
   case SYS_MODNOD:
      return (void*)sys_modnod((char*)arg1, (uid_t)arg2, (gid_t)arg3, (mode_t)arg4);
   case SYS_UNLINK:
      return (void*)sys_unlink((char*)arg1);
   case SYS_TRUNCATE:
      return (void*)sys_truncate((char*)arg1, (size_t)arg2);
   case SYS_LINK:
      return (void*)sys_link((char*)arg1, (char*)arg2, 0);
   case SYS_RENAME:
      return (void*)sys_link((char*)arg1, (char*)arg2, 1);
   case SYS_GETUID:
      return (void*)current->uid;
   case SYS_GETGID:
      return (void*)current->gid;
   case SYS_SETUID:
      return (void*)sys_setuid((uid_t)arg1);
   case SYS_SETGID:
      return (void*)sys_setgid((gid_t)arg1);
   case SYS_GETMAXFD:
      return (void*)COREMAXFD;
   case SYS_CLONE:
      return (void*)sys_clone();
   case SYS_FORK:
      return (void*)sys_fork();
   case SYS_WAITPID:
      return (void*)sys_waitpid((pid_t)arg1, (int*)arg2, (int)arg3);
   case SYS_REALLOC:
      return sys_realloc((void*)arg1, (size_t)arg2);
   case SYS_IOCTL:
      current->sys_errno = sys_ioctl((const char*)arg1, (ulong_t)arg2, (void*)arg3);
      if (current->sys_errno) {
         return (void*)-1;
      } else {
		 return (void*)0;
	  }
   case SYS_GETPID:
      return (void*)current->pid;
   case SYS_GETPPID:
      return (void*)current->parentpid;
   case SYS_GETPGID:
      return (void*)sys_getpgid((int)arg1);
   case SYS_SETPGID:
      return (void*)sys_setpgid((pid_t)arg1, (pid_t)arg2);
   case SYS_SETJMP:
      return (void*)sys_setjmp((long_t*)arg1);
   case SYS_LONGJMP:
      return (void*)sys_longjmp((long_t*)arg1);
   case SYS_GETRLIMIT:
      return (void*)sys_getrlimit((int)arg1, (void*)arg2);
   case SYS_GETERRNO:
      return (void*)sys_geterrno();
   case SYS_TLSADDR:
     printf(SYS_INFO "SYS_TLSADDR: arg1=%ld, arg2=%ld\n", arg1, arg2);
      return sys_tlsaddr((unsigned long int)arg1, (unsigned long int)arg2);  
   default:
      sys_printf(SYS_INFO "Unsupported syscall %d\n", number);
      break;
   }
   return NULL;
}
