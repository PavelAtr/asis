#ifdef DEBUG
#include "../include/tinysys.h"
#include <dlfcn.h>
#else
#include <tinysys.h>
#include "../libdl/libdl.h"
#endif

#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

char* initargv[2];

int_t sys_runinit()
{
   current->ctx.stack = sp - MAXSTACK + 64;
   initargv[0] = INIT;
   initargv[1] = NULL;
   pid_t init = sys_fork();
   if (init == 0) {
      sys_exec(initargv[0], initargv, NULL);
   } else {
      int_t ret;
      sys_waitpid(init, &ret, 0);
      return ret;
   }
   return 0;
}

extern FILE** current_fds;

int_t sys_exec(const char* file, char** argv, char** envp)
{
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
   current->program = sys_calloc(1, sizeof(prog));
   current->program->argc = argc;
   current->program->argv = argv;
   current->program -> nlink = 1;
   current->program->dlhandle = dlopen(file, RTLD_NOW | RTLD_DEEPBIND);
   if (!current->program->dlhandle) {
	  sys_printf(SYS_ERROR "EXEC dlopen %s FAILED\n", file);
      *current->sys_errno = ENOENT;
      goto fail;
   }
   sys_printf(SYS_DEBUG "EXEC dlopen %s\n", file);
   addr_t* syscall = dlsym(current->program->dlhandle, "syscall");
   addr_t* fds = dlsym(current->program->dlhandle, "core_fds");
   addr_t* retexit = dlsym(current->program->dlhandle, "retexit");
   current->sys_errno = dlsym(current->program->dlhandle, "errno");
   addr_t* environ = dlsym(current->program->dlhandle, "core_environ");
   void (*start)(int argc, char* const* argv) =
         dlsym(current->program->dlhandle, "_start");
   if (!syscall || !start || !fds || !retexit || !current->sys_errno || !environ) {
	  sys_printf(SYS_ERROR, "Main symbols at %s FAILED!\n", file);
      *current->sys_errno = ENOMEM;
      goto fail;
   }
   *syscall = (addr_t)&sys_syscall;
   *retexit = (addr_t)&sys_atexit;
   
   current->program->fds = copyfds(((proc*)current->parent)->program->fds);
   if (envp) {
		current->program->envp = copyenv(envp);
   } else {
		current->program->envp = copyenv(((proc*)current->parent)->program->envp);
   }
   current_fds = (FILE**)current->program->fds;
   current_env = current->program->envp;
   *fds = (addr_t)&current_fds;
   *environ = (addr_t)&current_env;
   
   current->flags &= ~PROC_CLONED;
   sys_printf(SYS_INFO "freememory=%ld\n", free_memory());
   start(argc, argv);
   switch_context;
   /* Never reach here */
   sys_printf(SYS_DEBUG "EXEC END (NOTREACHEBLE)\n");
   freeproc(current->forkret);
   return  0;
fail:
   return -1;
}

pid_t newproc()
{
   int_t i;
   for (i = 0; i < MAXPROC; i++)
      if (cpu[i] == NULL) {
         cpu[i] = sys_calloc(1, sizeof(proc));
         return i;
      }
   *current->sys_errno = ENOMEM;
   return -1;
}

void freeproc(pid_t pid)
{
   if (!pid_is_valid(pid)) {
      return;
   }
   if (!cpu[pid]) {
      return;
   }
   if (!(cpu[pid]->flags & PROC_CLONED)) {
      freefds(cpu[pid]);
      sys_free(cpu[pid]->ctx.stack);
      freeenv(cpu[pid]->program->envp);
   }
   dlclose(cpu[pid]->program->dlhandle);
   sys_free(cpu[pid]->program);
   sys_free(cpu[pid]);
   cpu[pid] = NULL;
}


pid_t sys_clone(void)
{
   sys_printf(SYS_DEBUG "CLONE pid=%d prog=%s\n", current->pid, current->program->argv[0]);
   pid_t ret = newproc();
   if (ret == -1) {
      return -1;
   }
   memcpy(cpu[ret], current, sizeof(proc));
   cpu[ret]->flags = PROC_RUNNING | PROC_NEW | PROC_CLONED;
   cpu[ret]->parent = current;
   cpu[ret]->pid = ret;
   cpu[ret]->parentpid = curpid;
   current->program->nlink++;
   cpu[ret]->ctx.stack = sys_malloc(MAXSTACK);
   return ret;
}

pid_t sys_fork()
{
   current->forkret = sys_clone();
   sys_printf(SYS_DEBUG "FORK in %s child=%d\n", current->program->argv[0], current->forkret);
   if (current->forkret == -1) {
      *current->sys_errno = ENOMEM;
      return -1;
   }
   cpu[current->forkret]->forkret = 0;
   cpu[current->forkret]->ret = -1;
   sys_printf(SYS_DEBUG "SWITCH pid=%d prog=%s\n", current->pid, current->program->argv[0]);
   switch_context;
   sys_printf(SYS_DEBUG "forkret=%d\n", (int)current->forkret);
   return current->forkret;
}

pid_t sys_waitpid(pid_t pid, int* wstatus, int options)
{
   sys_printf(SYS_DEBUG "WAITPID in %s child=%d\n", current->program->argv[0], pid);
   if (pid != -1) {
      if (!pid_is_valid(pid) || !cpu[pid]) {
         return -1;
      }
   }   
   *wstatus = -1;
   pid_t child = -1;
   bool_t found = 0;
   while(1) {
      if (pid == -1) {
         int_t i;
         for (i = 0; i < MAXPROC; i++) {
            if (!cpu[i]) {
               continue;
            }
            if (cpu[i]->parentpid == curpid) {
			   found = 1;	
			   if(!(cpu[i]->flags & PROC_RUNNING)) {
                  child = i;
                  goto end;
		       }
            }
         }
      } else {
         found = 1; 
         if (!(cpu[pid]->flags & PROC_RUNNING)) {
            child = pid;
            goto end;
         }
      }
      if (!found) {
	     return -1;
	  }
      switch_context;
   }
end:
   sys_printf(SYS_DEBUG "WAITPID END pid=%d prog=%s\n", current->pid, current->program->argv[0]);
   *wstatus = cpu[child]->ret;
   if (cpu[child]->flags & PROC_CLONED) {
	   goto end2;
   }
   cpu[child]->program->nlink--;
   if (cpu[child]->program->nlink <= 0) {
      freeproc(child);
   }
end2:   
   cpu[child] = NULL;
   return child;
}

void sys_atexit(int ret)
{
   sys_printf(SYS_DEBUG "ATEXIT=%d pid=%d prog=%s\n", ret, current->pid, current->program->argv[0]);
   current->ret = ret;
   current->flags &= ~PROC_RUNNING;
   current->flags |= PROC_ZOMBIE;
   switch_context;
}

