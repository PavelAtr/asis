#include <tinysys.h>
#include "../libdl/libdl.h"
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

char* initargv[2];

int_t sys_runinit()
{
   current->ctx.stack = sp - MAXSTACK + 64;
   initargv[0] = INIT;
   initargv[1] = NULL;
   pid_t init = sys_fork();
   if (init == 0) {
      sys_exec(initargv[0], initargv);
   } else {
      int_t ret;
      sys_waitpid(init, &ret, 0);
      return ret;
   }
   return 0;
}

int_t sys_exec(const char* file, char* const argv[])
{
   dlclose(current->dlhandle);
   int argc;
   for (argc = 0; argv[argc]; argc++);
   mountpoint* mount = sys_get_mountpoint(file);
   if (!mount) {
      *current->sys_errno = ENOENT;
      return -1;
   }
   const char* path = sys_calcpath(mount, file);
   if (!mount->mount_can_execute(mount->sbfs, path, current->uid, current->gid)) {
      *current->sys_errno = EPERM;
      return -1;
   }
   current->argc = argc;
   current->argv = argv;
   struct tinystat st;
   if (sys_stat(file, &st) == -1) {
      *current->sys_errno = ENOENT;
      return -1;
   }
   if (st.st_mode & S_ISUID) {
      current->uid = st.st_uid;
   } else {
      current->uid = current->uid;
   }
   if (st.st_mode & S_ISGID) {
      current->gid = st.st_gid;
   } else {
      current->gid = current->gid;
   }
   current->dlhandle = dlopen(file, 0);
   if (!current->dlhandle) {
      *current->sys_errno = ENOENT;
      return -1;
   }
   addr_t* syscall = dlsym(current->dlhandle, "syscall");
   addr_t* fds = dlsym(current->dlhandle, "fds");
   addr_t* atexit = dlsym(current->dlhandle, "atexit");
   current->sys_errno = dlsym(current->dlhandle, "errno");
   void __attribute__((sysv_abi)) (*start)(int argc, char* const* argv,
      char* const* envp)
      = dlsym(current->dlhandle, "_start");
   if (!syscall || !start || !fds || !atexit || !current->sys_errno) {
      *current->sys_errno = ENOMEM;
      return -1;
   }
   *syscall = (addr_t)&sys_syscall;
   *atexit = (addr_t)&sys_atexit;
   current->fds = copy_fds(((proc*)current->parent)->fds);
   current->envp = copyenv(((proc*)current->parent)->envp);
   *fds = (addr_t)current->fds;
   current->flags &= ~ PROC_CLONED;
   sys_printf(SYS_INFO "freememory=%ld\n", free_memory());
   start(argc, argv, current->envp);
   switch_context;
   /* Never reach here */
   sys_printf("EXEC END\n");
   freeproc(current->forkret);
   return  0;
}

pid_t sys_clone(void)
{
   sys_printf("CLONE\n");
   pid_t ret = newproc();
   if (ret == -1) {
      return -1;
   }
   memcpy(cpu[ret], current, sizeof(proc));
   cpu[ret]->flags = PROC_RUNNING | PROC_NEW | PROC_CLONED;
   if (current->dlhandle) {
      ((dl*)current->dlhandle)->nlink++;
   }
   cpu[ret]->parent = current;
   cpu[ret]->parentpid = curpid;
   cpu[ret]->ctx.stack = sys_malloc(MAXSTACK);
   return ret;
}

pid_t sys_fork()
{
   current->forkret = sys_clone();
   sys_printf("FORK in %s child=%d\n", current->argv[0], current->forkret);
   if (current->forkret == -1) {
      *current->sys_errno = ENOMEM;
      return -1;
   }
   cpu[current->forkret]->forkret = 0;
   cpu[current->forkret]->ret = -1;
   switch_context;
   sys_printf("forkret=%d\n", (int)current->forkret);
   return current->forkret;
}

pid_t sys_waitpid(pid_t pid, int* wstatus, int options)
{
   sys_printf("WAITPID in %s child=%d\n", current->argv[0], pid);
   *wstatus = -1;
   bool_t wait = 1;
   pid_t child = -1;
   while(wait) {
      if (pid == -1) {
         int_t i;
         bool_t child_exist = 0;
         for (i = 0; i < MAXPROC; i++) {
            if (!cpu[i]) {
               continue;
            }
            if (cpu[i]->parentpid == curpid) {
               child_exist = 1;
               if (!(cpu[i]->flags & PROC_RUNNING)) {
                  wait = 0;
                  child = i;
                  break;
               }
            }
         }
         if (!child_exist) {
            return -1;
         }
      } else {
         if (!pid_is_valid(pid) || !cpu[pid]) {
            return -1;
         }
         if (!(cpu[pid]->flags & PROC_RUNNING)) {
            child = pid;
            break;
         }
      }
      switch_context;
   }
   if (cpu[child]) {
      *wstatus = cpu[child]->ret;
      freeproc(child);
   }
   return child;
}

void sys_atexit(int ret)
{
   sys_printf("ATEXIT\n");
   current->ret = ret;
   current->flags &= ~PROC_RUNNING;
   switch_context;
}

