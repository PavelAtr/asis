#include <tinysys.h>
#include <syscall.h>
#include <stdarg.h>

long_t sys_syscall(long_t number, va_list vl)
{
   sys_printf("Syscall raised\n");
   char* char1;
   char* char2;
   size_t size1;
   size_t size2;
   off_t off1;
   mode_t mode1;
   long_t long1;
   void* ptr1;
   int int1;
   int int2;
   int int3;
   char** charr1;
   char** charr2;
   uid_t uid1;
   gid_t gid1;
   pid_t pid1;
   pid_t pid2;
   int* intptr1;
   va_list* valst;
   long_t* longptr;
   switch (number) {
   case SYS_MALLOC:
      size1 = va_arg(vl, size_t);
      return (addr_t)sys_malloc(size1);
      break;
   case SYS_FREE:
      ptr1 = va_arg(vl, void*);
      sys_free(ptr1);
      break;
   case SYS_MMAP:
      ptr1 = va_arg(vl, void*);
      size1 = va_arg(vl, size_t);
      int1 = va_arg(vl, int);
      int2 = va_arg(vl, int);
      int3 = va_arg(vl, int);
      off1 = va_arg(vl, off_t);
      return (addr_t)sys_mmap(ptr1, size1, int1, int2, int3, off1);
      break;
   case SYS_MUNMAP:
      ptr1 = va_arg(vl, void*);
      size1 = va_arg(vl, size_t);
      return sys_munmap(ptr1, size1);
      break;
   case SYS_FWRITE:
      char1 = va_arg(vl, char*);
      ptr1 = va_arg(vl, void*);
      size1 = va_arg(vl, size_t);
      size2 = va_arg(vl, size_t);
      return sys_afwrite(char1, ptr1, size1, size2);
      break;
   case SYS_FREAD:
      char1 = va_arg(vl, char*);
      ptr1 = va_arg(vl, void*);
      size1 = va_arg(vl, size_t);
      size2 = va_arg(vl, size_t);
      return sys_afread(char1, ptr1, size1, size2);
      break;
   case SYS_FSTAT:
      char1 = va_arg(vl, char*);
      ptr1 = va_arg(vl, void*);
      return sys_stat(char1, ptr1);
      break;
   case SYS_DBG:
      ptr1 = va_arg(vl, void*);
      sys_printf(SYS_INFO "sys_debug %p\n", ptr1);
      break;
   case SYS_USLEEP:
      long1 = va_arg(vl, long_t);
      return sys_usleep(long1);
      break;
   case SYS_EXECVE:
      char1 = va_arg(vl, char*);
      charr1 = va_arg(vl, char**);
      charr2 = va_arg(vl, char**);
      return sys_exec(char1, charr1, charr2);
      break;
   case SYS_READDIR:
      char1 = va_arg(vl, char*);
      int2 = va_arg(vl, int);
      return (long_t)sys_readdir(char1, int2);
   case SYS_MKNOD:
      char1 = va_arg(vl, char*);
      mode1 = va_arg(vl, mode_t);
      return sys_mknod(char1, mode1);
   case SYS_MODNOD:
      char1 = va_arg(vl, char*);
      uid1 = va_arg(vl, uid_t);
      gid1 = va_arg(vl, gid_t);
      mode1 = va_arg(vl, mode_t);
      return sys_modnod(char1, uid1, gid1, mode1);
   case SYS_UNLINK:
      char1 = va_arg(vl, char*);
      return sys_unlink(char1);
   case SYS_TRUNCATE:
      char1 = va_arg(vl, char*);
      off1 = va_arg(vl, off_t);
      return sys_truncate(char1, off1);
   case SYS_LINK:
      char1 = va_arg(vl, char*);
      char2 = va_arg(vl, char*);
      return sys_link(char1, char2, 0);
   case SYS_RENAME:
      char1 = va_arg(vl, char*);
      char2 = va_arg(vl, char*);
      return sys_link(char1, char2, 1);
   case SYS_GETUID:
      return current->uid;
   case SYS_GETGID:
      return current->gid;
   case SYS_SETUID:
      uid1 = va_arg(vl, uid_t);
      return sys_setuid(uid1);
   case SYS_SETGID:
      gid1 = va_arg(vl, gid_t);
      return sys_setgid(gid1);
   case SYS_GETMAXFD:
      return COREMAXFD;
   case SYS_CLONE:
      return sys_clone();
   case SYS_FORK:
      return sys_fork();
   case SYS_WAITPID:
      pid1 = va_arg(vl, pid_t);
      intptr1 = va_arg(vl, int*);
      int1 = va_arg(vl, int);
      return sys_waitpid(pid1, intptr1, int1);
   case SYS_REALLOC:
      ptr1 = va_arg(vl, void*);
      size1 = va_arg(vl, size_t);
      return (addr_t)sys_realloc(ptr1, size1);
   case SYS_IOCTL:
      char1 = va_arg(vl, char*);
      long1 = va_arg(vl, long_t);
      valst = va_arg(vl, va_list*);
      current->sys_errno = sys_ioctl(char1, long1, valst);
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
      pid1 = va_arg(vl, pid_t);
      return sys_getpgid(pid1);
   case SYS_SETPGID:
      pid1 = va_arg(vl, pid_t);
      pid2 = va_arg(vl, pid_t);
      return sys_setpgid(pid1, pid2);
   case SYS_SETJMP:
      longptr = va_arg(vl, long_t*);
      return sys_setjmp(longptr);
   case SYS_LONGJMP:
      longptr = va_arg(vl, long_t*);
      return sys_longjmp(longptr);
   case SYS_GETRLIMIT:
      int1 = va_arg(vl, int);
      ptr1 = va_arg(vl, void*);
      return sys_getrlimit(int1, ptr1);
   case SYS_GETERRNO:
      return sys_geterrno();
   default:
      sys_printf(SYS_INFO "Unsupported syscall %d\n", number);
      break;
   }
   return 0;
}
