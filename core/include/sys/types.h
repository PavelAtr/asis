#ifndef _TYPES_H
#define _TYPES_H

typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef unsigned int mode_t;
typedef int clockid_t;
typedef void* timer_t;
typedef unsigned long ino_t;
typedef unsigned long fsblkcnt_t;
typedef unsigned long fsfilcnt_t; 
typedef int sig_atomic_t;
typedef unsigned long rlim_t;

#ifdef UEFI
typedef unsigned long long size_t;
typedef unsigned long long off_t;
typedef unsigned long long off64_t;
typedef long long ssize_t;
typedef unsigned long long time_t;
typedef long long suseconds_t;
typedef long long long_t;
typedef unsigned long long ulong_t;
typedef long long long64_t;
typedef unsigned long long ulong64_t;
typedef unsigned long long addr_t;
typedef unsigned long long u_long;
#else
typedef unsigned long size_t;
typedef long  off_t;
typedef unsigned long  off64_t;
typedef long ssize_t;
typedef long time_t;
typedef long suseconds_t;
typedef long long_t;
typedef unsigned long ulong_t;
typedef long long64_t;
typedef unsigned long ulong64_t;
typedef unsigned long addr_t;
typedef unsigned long u_long;
#endif
typedef int pid_t;
typedef unsigned long dev_t;
typedef unsigned char u_char;

typedef ulong64_t len_t;
typedef ulong64_t counter_t;
typedef int int_t;
typedef int errno_t;

typedef unsigned char bool_t;
typedef unsigned int u_int32_t;

#ifndef __cplusplus
typedef short  char16_t;
#endif

#ifndef __cplusplus
typedef int  char32_t;
#endif

typedef unsigned int __u32;
typedef unsigned short __u16;
typedef unsigned char __u8;
typedef int __s32;
typedef short __s16;
typedef char __s8;
typedef long64_t __s64;
typedef ulong64_t __u64;
typedef size_t __kernel_size_t;

#endif
