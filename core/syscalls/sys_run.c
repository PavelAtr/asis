#include <tinysys.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#undef fds

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

extern AFILE** current_fds;

int_t sys_exec(const char* file, char** argv, char** envp)
{
   int argc;
   for (argc = 0; argv[argc]; argc++);
   mountpoint* mount = sys_get_mountpoint(file);
   if (!mount) {
      current->sys_errno = ENOENT;
      return -1;
   }
   const char* path = sys_calcpath(mount, file);
   if (!mount->mount_can_execute(mount->sbfs, path, current->uid, current->gid)) {
      current->sys_errno = EPERM;
      return -1;
   }
   struct tinystat st;
   if (sys_stat(file, &st) == -1) {
      current->sys_errno = ENOENT;
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
   
   if (current->flags & PROC_CLONED) {
	   current->program->nlink--;
	   if (current->program -> nlink <= 0) {
		   sys_printf(SYS_ERROR "SYS_EXEC: Memory leak in current->program structure\n");
	   }
       current->program = sys_calloc(1, sizeof(prog));
   }
   current->program->argc = argc;
   current->program->argv = argv;
   current->program -> nlink = 1;

   current->program->dlhandle = sys_dlopen(file, 0);
   if (!current->program->dlhandle) {
	  sys_printf(SYS_ERROR "EXEC dlopen %s FAILED\n", file);
      current->sys_errno = ENOENT;
      goto fail;
   }

   int (*start)(int argc, char*** argv, char*** envp, AFILE*** fds, errno_t** cerrno, void* syscall_func, void* retexit_func) =
         sys_dlsym(current->program->dlhandle, "_start");
   if (envp) {
		current->program->envp = copyenv(envp);
   } else {
		current->program->envp = copyenv(((proc*)current->parent)->program->envp);
   }
   current_env = current->program->envp;
   current_argv = current->program->argv;
   current_errno = &current->sys_errno;
   
   current->flags &= ~PROC_CLONED;
   sys_printf(SYS_INFO "freememory=%ld\n", free_memory());
   int ret = start(argc, &current_argv, &current_env, &current_fds, &current_errno, &sys_syscall, &sys_atexit);
   switch_context;
   /* Never reach here */
   sys_printf(SYS_DEBUG "EXEC END (NOTREACHEBLE)\n");
   freeproc(current->forkret);
   return  ret;
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
   current->sys_errno = ENOMEM;
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
      freeenv(cpu[pid]->program->envp);
   }
   freefds(cpu[pid]);
   sys_free(cpu[pid]->ctx.stack);
   cpu[pid]->program->nlink--;
   if (cpu[pid]->program->nlink <= 0) {
      sys_dlclose(cpu[pid]->program->dlhandle);
      sys_free(cpu[pid]->program);
   }
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
   cpu[ret]->fds = copyfds(current->fds);

   return ret;
}

pid_t sys_fork()
{
   current->forkret = sys_clone();
   sys_printf(SYS_DEBUG "FORK in %s child=%d\n", current->program->argv[0], current->forkret);
   if (current->forkret == -1) {
      current->sys_errno = ENOMEM;
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
   sys_printf(SYS_DEBUG "WAITPID END pid=%d prog=%s child=%d\n", current->pid, current->program->argv[0], child);
   *wstatus = cpu[child]->ret;
   freeproc(child);
   cpu[child] = NULL;
   return child;
}

void sys_atexit(int ret)
{
   sys_printf(SYS_DEBUG "ATEXIT=%d pid=%d prog=%s\n", ret, current->pid, current->program->argv[0]);
   current->ret = ret;
   current->flags &= ~PROC_RUNNING;
   current->flags |= PROC_ENDED;
   switch_context;
}

