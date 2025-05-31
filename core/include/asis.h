#ifndef _TINYSYS_H
#define _TINYSYS_H

#include "sys/types.h"
#include <stdarg.h>

#define S_ISUID  04000
#define S_ISGID  02000
#define S_ISVTX  01000

#define INIT "/asis/bin/shell"

#define malloc(s) sys_malloc(s)
#define free(p) sys_free(p)
#define calloc(n, s) sys_calloc(n, s)
#define printf(fmt, ...) sys_printf(fmt, __VA_ARGS__)
#define mmap(addr, length, prot, flags, fd, offset) sys_mmap(addr, length, prot, flags, fd, offset)
#define munmap(addr, length) sys_munmap(addr, length)
#define afread(pth, p, s, o) sys_afread(pth, p, s, o)
#define freenull(pp) \
    if (*pp) { \
    free((void*)*pp); \
    *pp = NULL; \
    }

int_t sys_exec(char* file, char** argv, char** envp);
int_t sys_runinit();

int_t sys_stat(const char* pathname, void* statbuf);
len_t sys_afread(const char* path, void* ptr, len_t size, len_t off);
len_t sys_afwrite(const char* path, const void* ptr, len_t size, len_t off);
void* sys_readdir(char* pathname, int_t ndx);
int_t sys_mknod(const char* pathname, mode_t mode);
int_t sys_modnod(const char* pathname, uid_t uid, gid_t gid, mode_t mode);
int_t sys_unlink(const char *pathname);
int_t sys_truncate(const char *pathname, size_t length);
int_t sys_link(const char *oldpath, const char *newpath, bool_t move);

#define MEMSIZE	10000000

void* sys_mmap(void* addr, size_t length, int prot, int flags, int f, off_t offset);
int sys_munmap(void* addr, size_t length);
void* sys_malloc(size_t size);
void* sys_calloc(size_t nmemb, size_t size);
extern int curmem;
void sys_free(void *ptr);
void sys_prog_free(void *ptr);
long64_t sys_syscall(int number, long64_t arg1, long64_t arg2, long64_t arg3, long64_t arg4, long64_t arg5, long64_t arg6);
int sys_usleep(long_t usecs);

#define MAXDEV 5

typedef struct {
  const char* file;
  void* devparams;
  int_t type;
  void (*dev_seek)(void* devsb, len_t offset);
  len_t (*dev_write)(void* devsb, const void* buffer, len_t size);
  len_t (*dev_read)(void* devsb, void* buffer, len_t size);
  errno_t (*dev_ioctl)(void* devsb, ulong_t request, va_list vl);
} device;

extern device devices[MAXDEV];
device* sys_get_device_byname(const char* path, mode_t devtype);

#define MAXMOUNT 5

typedef struct {
  const char* path;
  void* sbfs;
  errno_t (*mount_mknod)(void* sbfs, const char *pathname, uid_t uid, gid_t gid, mode_t mode);
  errno_t (*mount_modnod)(void* sbfs, const char* pathname, uid_t uid, gid_t gid, mode_t mode);
  errno_t (*mount_rmnod)(void* sbfs, const char *pathname, uid_t curuid, gid_t curgid);
  errno_t (*mount_link)(void* sb, const char* src, const char* dst, bool_t move, uid_t uid, gid_t gid);
  errno_t (*mount_truncate)(void* sb, const char *pathname, len_t len);
  errno_t (*mount_stat)(void* sbfs, const char* pathname, void* statbuf);
  len_t (*mount_fread)(void* sbfs, const char* path, void* ptr, len_t size, len_t off);
  len_t(*mount_fwrite)(void* sbfs, const char* path, const void* ptr, len_t size, len_t off);
  void* (*mount_readdir)(void* sbfs, const char* path, int ndx);
  bool_t (*mount_can_read)(void* sbfs, const char* path, uid_t uid, gid_t gid);
  bool_t (*mount_can_write)(void* sbfs, const char* path, uid_t uid, gid_t gid);
  bool_t (*mount_can_execute)(void* sbfs, const char* path, uid_t uid, gid_t gid);
} mountpoint;

extern mountpoint mountpoints[MAXMOUNT];

mountpoint* sys_get_mountpoint(const char* file);
const char* sys_calcpath(mountpoint* mount, const char* file);
int sys_mount(const char* blk, const char* mount, const char* fstype, const char* options);
int sys_umount(const char* dir);

int sys_printf(const char* format, ...);
#define SYS_DEBUG "debug:\t"
#define SYS_INFO "info:\t"
#define SYS_ERROR "error:\t"

typedef struct {
  char* stack;
  char* sp;
} context;

typedef struct {
  int argc;
  char**  argv;
  char** envp;
  void* dlhndl;
  int* dlnlink;	
  int_t flags;
  void** fds;
  void* parent;
  pid_t pid;
  pid_t parentpid;
  errno_t sys_errno;
  uid_t uid;
  gid_t gid;
  context ctx;
  int_t ret;
  pid_t forkret;
  pid_t pgid;
  addr_t* tlsid;
} proc;

#define PROC_RUNNING 0x01
#define PROC_NEW 0x02
#define PROC_CLONED 0x04
#define PROC_ENDED 0x08

extern proc* current;
extern proc* systask;

void init_proc();

char** copyenv(char** e);
void freeenv(char** envp);

struct tinystat {
  mode_t	st_mode;     /* File type and mode */
  uid_t	st_uid;      /* User ID of owner */
  gid_t	st_gid;      /* Group ID of owner */
  size_t	st_size;
  short	st_major;
  short	st_minor;
};

#define MAX_PATH_PART 256

struct tinydirent {
  char           d_name[MAX_PATH_PART];
};

typedef struct {
  bool_t (*capable)(int_t cap);
  bool_t (*in_group)(gid_t gid);
} secmodel;

extern secmodel* security;
#define SETUIDPROC "/tinysys/shell"
int_t sys_setuid(uid_t uid);
int_t sys_setgid(gid_t gid);

#define COREMAXFD 20
#define COREMAXENV 20

void** copyfds(void** infds);
void freefds(proc* task);
void** cloexecfds(void** infds);
__attribute__((sysv_abi)) void sys_atexit(int ret);

#define MAXPROC 20
extern proc* cpu[MAXPROC];
extern int_t curpid;
pid_t newproc();
void freeproc(pid_t pid);
#define pid_is_valid(pid) (pid >= 0 && pid < MAXPROC)

extern proc* current;


pid_t sys_clone(void);
pid_t sys_fork(void);
pid_t sys_waitpid(pid_t pid, int* wstatus, int options);

typedef __attribute__((sysv_abi)) int (*startfunction)
   (int argc, char*** argv, char*** envp, void*** fds,
     void* syscall_func, void* retexit_func);

#define MAXSTACK (8192 * 1024)

#define setsp(addr) __asm__("mov %0, %%rsp\n" \
           : \
           : "r" (addr))

#define getsp(addr) __asm__("mov %%rsp, %0\n" \
           : "=r" (addr)\
           : )

register char* sp __asm__("rsp");
extern char* mainsp;

void switch_task();

#define switch_context \
	if (current) sys_printf(SYS_DEBUG "switch before stack=%p sp=%p depth=%ld\n", current->ctx.stack, sp, sp - current->ctx.stack); \
	switch_task(); \
	sys_printf(SYS_DEBUG "switch after stack=%p sp=%p depth=%ld\n", current->ctx.stack, sp, sp - current->ctx.stack);
/* #define switch_context switch_task(); */

void trap_segfault();

void init_memory(void* base, size_t size);
size_t free_memory(void);
void* sys_realloc(void* ptr, size_t size);

errno_t sys_ioctl(const char* path, ulong_t request, va_list* vl);

int_t sys_setpgid(pid_t pid, pid_t pgid);
int_t sys_getpgid(pid_t pid);

int_t sys_setjmp(long_t* env);
int_t sys_longjmp(long_t* env);
#define JMP_STACK 0
#define JMP_SP 1
#define JMP_DEPTH 2

void* sys_dlopen(const char *filename, int flags);
int sys_dlclose(void *handle);
void* sys_dlsym(void * handle, const char * symbol);
void sys_dltls(void* handle, unsigned long module_id);
int sys_getrlimit(int resource, void* r);

extern char** current_envp;
extern char** current_argv;

errno_t sys_geterrno();
void* alloc_stack(size_t size);
void free_stack(void* stackbase, size_t size);

#endif
