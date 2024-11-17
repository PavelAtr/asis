#ifndef _TINYSYS_H
#define _TINYSYS_H

#include "sys/types.h"

#ifdef UEFI
#define O_CLOEXEC 0x01
#define O_RDONLY 0x02
#define O_RDWR 0x04
#define O_WRONLY 0x08
#define O_CREAT 0x10
#define O_TRUNC 0x20
#define O_APPEND 0x40

#define S_ISUID  04000
#define S_ISGID  02000
#define S_ISVTX  01000
#else
#endif

#define INIT "/tinysys/bin/shell"

//#define PATH_MAX 512

int_t sys_exec(const char* file, char* const argv[]);
int_t sys_runinit();

int_t sys_stat(const char* pathname, void* statbuf);
len_t sys_fread(const char* path, void* ptr, len_t size, len_t off);
len_t sys_fwrite(const char* path, const void* ptr, len_t size, len_t off);
void* sys_readdir(char* pathname, int_t ndx);
int_t sys_mknod(const char* pathname, mode_t mode);
int_t sys_modnod(const char* pathname, uid_t uid, gid_t gid, mode_t mode);
int_t sys_unlink(const char *pathname);
int_t sys_truncate(const char *pathname, size_t length);
int_t sys_link(const char *oldpath, const char *newpath, bool_t move);

#define MEMSIZE	256000

void* sys_mmap(void* addr, size_t length, int prot, int flags, int f, off_t offset);
int sys_munmap(void* addr, size_t length);
void* sys_malloc(size_t size);
extern int curmem;
void sys_free(void *ptr);
void sys_prog_free(void *ptr);
long_t sys_syscall(long_t number, ...);
int sys_usleep(long_t usecs);

#define MAXDEV 5

typedef struct {
	const char* file;
	void* devparams;
	int_t type;
	void (*dev_seek)(void* devsb, len_t offset);
	len_t (*dev_write)(void* devsb, const void* buffer, len_t size);
	len_t (*dev_read)(void* devsb, void* buffer, len_t size);
	errno_t (*dev_ioctl)(void* devsb, ulong_t request, ...);
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

int sys_printf(const char* format, ...);
#define SYS_INFO "info: "
#define SYS_ERROR "error: "


typedef struct {
	void* stack;
	void* sp;
} context;

typedef struct {
	int_t flags;
	void* parent;
	pid_t parentpid;
	int argc;
	char** argv;
	char** envp;
	errno_t sys_errno;
	uid_t uid;
	gid_t gid;
	void* fds;
	void* dlhandle;
	context ctx;
	int_t ret;
	pid_t forkret;
} proc;

#define PROC_RUNNING 0x01
#define PROC_NEW 0x02
#define PROC_CLONED 0x04


extern proc* current;
extern proc* systask;

void init_proc();

char** copyenv(char*const* e);
void freeenv(char*const* envp);

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

void* copy_fds(void* infds);
void free_fds(proc* task);
void sys_atexit(int ret);

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


#define MAXSTACK 8192

#define setsp(sp) __asm__("mov %0, %%rsp\n" \
           : \
           : "r" (sp))

#define getsp(sp) __asm__("mov %%rsp, %0\n" \
           : "=r" (sp)\
           : )

register void* sp __asm__("rsp");

void switch_task();

#define switch_context \
	if (current) sys_printf("switch before stack=%p sp=%p depth=%ld\n", current->ctx.stack, sp, (char*)current->ctx.stack + MAXSTACK - (char*)sp); \
	switch_task(); \
	sys_printf("switch after stack=%p sp=%p depth=%ld\n", current->ctx.stack, sp, (char*)current->ctx.stack + MAXSTACK - (char*)sp);

void trap_segfault();

void init_memory(void* base, size_t size);
size_t free_memory(void);


#endif
