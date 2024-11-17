#ifndef _SYSCALL_H
#define _SYSCALL_H

#ifdef UEFI_KERNEL
extern long __attribute__((ms_abi)) (*syscall)(long number, ...);
#else
extern long (*syscall)(long number, ...);
#endif

#define SYS_DEBUG 0
#define SYS_FWRITE 1
#define SYS_FREAD 2
#define SYS_FSTAT 3
#define SYS_USLEEP 4
#define SYS_READDIR 5
#define SYS_GETERRNO 6
#define SYS_MKNOD 7
#define SYS_UNLINK 8
#define SYS_MODNOD 9
#define SYS_SETUID 10
#define SYS_SETGID 11
#define SYS_GETUID 12
#define SYS_GETGID 13
#define SYS_SETERRNO 14
#define SYS_MALLOC 15
#define SYS_FREE 16
#define SYS_MMAP 17
#define SYS_MUNMAP 18
#define SYS_EXECVE 19
#define SYS_TRUNCATE 20
#define SYS_LINK 21
#define SYS_RENAME 22
#define SYS_GETMAXFD 23
#define SYS_CLONE 24
#define SYS_FORK 25
#define SYS_WAITPID 26


#endif
