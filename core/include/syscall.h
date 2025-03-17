#ifndef _SYSCALL_H
#define _SYSCALL_H

#include <stdarg.h>
#include <errno.h>

#ifndef __ASYS__
#ifdef UEFI_KERNEL
extern long __attribute__((ms_abi)) (*sys_syscall)(long number, va_list args);
#else
extern long (*sys_syscall)(long number, va_list args);
#endif
#endif


#define SYS_DBG 0
#define SYS_FWRITE 1
#define SYS_FREAD 2
#define SYS_FSTAT 3
#define SYS_USLEEP 4
#define SYS_READDIR 5
#define SYS_MKNOD 6
#define SYS_UNLINK 7
#define SYS_MODNOD 8
#define SYS_SETUID 9
#define SYS_SETGID 10
#define SYS_GETUID 11
#define SYS_GETGID 12
#define SYS_MALLOC 13
#define SYS_FREE 14
#define SYS_MMAP 15
#define SYS_MUNMAP 16
#define SYS_EXECVE 17
#define SYS_TRUNCATE 18
#define SYS_LINK 19
#define SYS_RENAME 20
#define SYS_GETMAXFD 21
#define SYS_CLONE 22
#define SYS_FORK 23
#define SYS_WAITPID 24
#define SYS_REALLOC 25
#define SYS_IOCTL 26
#define SYS_GETPID 27
#define SYS_GETPPID 28
#define SYS_GETPGID 29
#define SYS_SETPGID 30
#define SYS_SETJMP 31
#define SYS_LONGJMP 32
#define SYS_GETRLIMIT 33
#define SYS_GETERRNO 34

static inline long syscall(long number, ...)
{
   va_list vl;
   va_start(vl, number);
   long ret = sys_syscall(number, vl);
   errno = sys_syscall(SYS_GETERRNO, NULL);
   return ret;
}


#endif
