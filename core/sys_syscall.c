#include <tinysys.h>
#include <syscall.h>
#include <stdarg.h>

long_t sys_syscall(long_t number, ...)
{
   va_list vl;
   va_start(vl, number);
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
   uid_t uid1;
   gid_t gid1;
   pid_t pid1;
   int* intptr1;
   switch (number) {
   case SYS_MALLOC:
      size1 = va_arg(vl, size_t);
      va_end(vl);
      return (addr_t)sys_malloc(size1);
      break;
   case SYS_FREE:
      ptr1 = va_arg(vl, void*);
      va_end(vl);
      sys_free(ptr1);
      break;
   case SYS_MMAP:
      ptr1 = va_arg(vl, void*);
      size1 = va_arg(vl, size_t);
      int1 = va_arg(vl, int);
      int2 = va_arg(vl, int);
      int3 = va_arg(vl, int);
      off1 = va_arg(vl, off_t);
      va_end(vl);
      return (addr_t)sys_mmap(ptr1, size1, int1, int2, int3, off1);
      break;
   case SYS_MUNMAP:
      ptr1 = va_arg(vl, void*);
      size1 = va_arg(vl, size_t);
      va_end(vl);
      return sys_munmap(ptr1, size1);
      break;
   case SYS_FWRITE:
      char1 = va_arg(vl, char*);
      ptr1 = va_arg(vl, void*);
      size1 = va_arg(vl, size_t);
      size2 = va_arg(vl, size_t);
      va_end(vl);
      return sys_fwrite(char1, ptr1, size1, size2);
      break;
   case SYS_FREAD:
      char1 = va_arg(vl, char*);
      ptr1 = va_arg(vl, void*);
      size1 = va_arg(vl, size_t);
      size2 = va_arg(vl, size_t);
      va_end(vl);
      return sys_fread(char1, ptr1, size1, size2);
      break;
   case SYS_FSTAT:
      char1 = va_arg(vl, char*);
      ptr1 = va_arg(vl, void*);
      va_end(vl);
      return sys_stat(char1, ptr1);
      break;
   case SYS_DEBUG:
      ptr1 = va_arg(vl, void*);
      va_end(vl);
      sys_printf(SYS_INFO "sys_debug %p\n", ptr1);
      break;
   case SYS_USLEEP:
      long1 = va_arg(vl, long_t);
      va_end(vl);
      return sys_usleep(long1);
      break;
   case SYS_EXECVE:
      char1 = va_arg(vl, char*);
      charr1 = va_arg(vl, char**);
      va_end(vl);
      return sys_exec(char1, charr1);
      break;
   case SYS_READDIR:
      char1 = va_arg(vl, char*);
      int2 = va_arg(vl, int);
      va_end(vl);
      return (long_t)sys_readdir(char1, int2);
   case SYS_SETERRNO:
      int1 = va_arg(vl, int);
      va_end(vl);
      current->sys_errno = int1;
      return 0;
   case SYS_GETERRNO:
      va_end(vl);
      return current->sys_errno;
   case SYS_MKNOD:
      char1 = va_arg(vl, char*);
      mode1 = va_arg(vl, mode_t);
      va_end(vl);
      return sys_mknod(char1, mode1);
   case SYS_MODNOD:
      char1 = va_arg(vl, char*);
      uid1 = va_arg(vl, uid_t);
      gid1 = va_arg(vl, gid_t);
      mode1 = va_arg(vl, mode_t);
      va_end(vl);
      return sys_modnod(char1, uid1, gid1, mode1);
   case SYS_UNLINK:
      char1 = va_arg(vl, char*);
      va_end(vl);
      return sys_unlink(char1);
   case SYS_TRUNCATE:
      char1 = va_arg(vl, char*);
      off1 = va_arg(vl, off_t);
      va_end(vl);
      return sys_truncate(char1, off1);
   case SYS_LINK:
      char1 = va_arg(vl, char*);
      char2 = va_arg(vl, char*);
      va_end(vl);
      return sys_link(char1, char2, 0);
   case SYS_RENAME:
      char1 = va_arg(vl, char*);
      char2 = va_arg(vl, char*);
      va_end(vl);
      return sys_link(char1, char2, 1);
   case SYS_GETUID:
      va_end(vl);
      return current->uid;
   case SYS_GETGID:
      va_end(vl);
      return current->gid;
   case SYS_SETUID:
      uid1 = va_arg(vl, uid_t);
      va_end(vl);
      return sys_setuid(uid1);
   case SYS_SETGID:
      gid1 = va_arg(vl, gid_t);
      va_end(vl);
      return sys_setgid(gid1);
   case SYS_GETMAXFD:
      va_end(vl);
      return COREMAXFD;
   case SYS_CLONE:
      va_end(vl);
      return sys_clone();
   case SYS_FORK:
      va_end(vl);
      return sys_fork();
   case SYS_WAITPID:
      pid1 = va_arg(vl, pid_t);
      intptr1 = va_arg(vl, int*);
      int1 = va_arg(vl, int);
      va_end(vl);
      return sys_waitpid(pid1, intptr1, int1);
   default:
      va_end(vl);
      sys_printf(SYS_INFO "Unsupported syscall %d\n", number);
      break;
   }
   return 0;
}
