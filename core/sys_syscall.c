/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include "../config.h"
#include <asis.h>
#include "../config.h"
#include <syscall.h>

#include <stddef.h>

void* sys_syscall(int number, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5, void* arg6)
{
   switch (number) {
   case SYS_MALLOC:
      return sys_malloc((size_t) arg1);
      break;
   case SYS_FREE:
      sys_free(arg1);
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
      sys_printf((char*)arg1);
      sys_printf("%p\n", arg2);
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
      return (void*)sys_fork(0);
   case SYS_VFORK:
      return (void*)sys_fork(1);
   case SYS_WAITPID:
      return (void*)sys_waitpid((pid_t)arg1, (int*)arg2, (int)arg3);
   case SYS_REALLOC:
      return sys_realloc((void*)arg1, (size_t)arg2);
   case SYS_IOCTL:
      return (void*) sys_ioctl((const char*)arg1, (ulong_t)arg2, (void*)arg3, (void*)arg4, (void*)arg5, (void*)arg6);
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
   case SYS_SHARED:
      return (void*)sys_shared((void**)arg1, (const char*)arg2, (const char*)arg3, (const char*)arg4, (size_t*)arg5);
   case SYS_FREESHARED:
      sys_delshared((const char*)arg1, (const char*)arg2);
      return NULL;
   case SYS_THREADEND:
      sys_threadend();
      break;
   case SYS_LISTEN:
      return (void*) sys_listen(arg1);
   case SYS_CONNECT:
      return (void*) sys_connect(arg1, arg2);
   case SYS_TLS:
      return sys_tls_get_addr ((unsigned long)arg1, (unsigned long)arg2);
   case SYS_SETENVIRON:
      current->envp = arg1;
      return NULL;
   case SYS_SETFDS:
      current->fds = arg1;
      return NULL;
   case SYS_CHDIR:
      return (void*)sys_chdir((char*)arg1);
   case SYS_GETCWD:
      return (void*)get_current_dir_name();
   case SYS_MALLOCUSABLE:
      return (void*)sys_malloc_usable_size(arg1); 
   default:
      sys_printf(SYS_INFO "Unsupported syscall %d\n", number);
      break;
   }
   return NULL;
}

