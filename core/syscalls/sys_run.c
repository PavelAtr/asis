#include <asis.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "../../userspace/alibdl/libdl.h"
#include <start.h>
#include <unistd.h>
#include <sys/wait.h>

#undef fds
#undef environ

char* initargv[2];
char* mainsp;

int_t sys_runinit()
{
   current->ctx.stack = mainsp - MAXSTACK;
   sys_printf("sys_runinit: stack=%p sp=%p\n", current->ctx.stack, sp);
   initargv[0] = INIT;
   initargv[1] = NULL;
   pid_t init = sys_fork(0);
   if (init == 0) {
      sys_exec(initargv[0], initargv, sys.envp);
      return -1;
   } else {
      int_t ret;
      sys_waitpid(init, &ret, 0);
      return ret;
   }
   return 0;
}

int_t* new_dlnlink(void* dlhandle)
{
   int_t i;
   for (i = 0; i < MAXPROC; i++)
      if (cpu[i] != NULL) {
         if (cpu[i]->dlhndl == dlhandle && cpu[i] != current)
         {
            return cpu[i]->dlnlink;
         }
      }   
   int_t* ret = sys_calloc(1, sizeof(int_t));
   *ret = 0;
   return ret;
}

errno_t sys_exec(char* file, char** inargv, char** envp)
{
   sys_printf(SYS_DEBUG "EXEC %s\n", file);
   int argc;
   int ret;
   for (argc = 0; inargv[argc]; argc++);
   //deinit_tls(current);
   current->dtv = NULL;
   if (envp && curpid != 1) {
      freeenv(current->envp);
		current->envp = envp;
   } 
   (*current->dlnlink)--;
   if (!(current->flags & PROC_EXECED)) {
      current->dlnlink = new_dlnlink(current->dlhndl);
   } else {
      if ((*current->dlnlink) <= 0) {
		   sys_dlclose(current->dlhndl);
      }
   }
   mountpoint* mount;
   const char* path = sys_calcpath(&mount, file);
   if (!mount) {
      current->dlhndl = NULL;
      ret = ENOENT;
      goto fail;
   }
   if (!mount->mount_can_execute(mount->sbfs, path, current->uid, current->gid)) {
      current->dlhndl = NULL;
      ret = EPERM;
      goto fail;
   }
   struct stat st;
   if (sys_stat(file, &st) == -1) {
      current->dlhndl = NULL;
      ret = ENOENT;
      goto fail;
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
   
   current->argc = argc;
   current->argv = inargv;
   current->cwd = strdup("/");
   current->dlhndl = sys_dlopen(file, 0);
   if (!current->dlhndl) {
	   sys_printf(SYS_ERROR "EXEC dlopen %s FAILED\n", file);
      ret = ENOENT;
      goto fail;
   }
   (*current->dlnlink)++;
   sys_printf("EXEC dlnlink %p=%d\n", current->dlnlink, *current->dlnlink);
   init_tls(current);
   current->start = (void*)(((dlhandle*)current->dlhndl)->obj->dl_elf->hdr->e_entry + 
      ((dlhandle*)current->dlhndl)->obj->dl_elf->exec);
   current->flags |= PROC_EXECED;
   printf("EXEC START %s argv=%p envp=%p fds=%p syscall=%p retexit=%p\n", 
      file, current->argv, current->envp, current->fds, &sys_syscall, &sys_atexit);
   ret = sys_runoncpu(current->start, current, sys_getcpu());
   /* Never reach here */
   sys_printf(SYS_DEBUG "EXEC END (NOTREACHEBLE)\n");
   return  ret;
fail:
      current->flags = PROC_ENDED | PROC_DESTROYED;
      current->forkret = -1;
      switch_context;
}

pid_t newproc()
{
   int_t i;
   for (i = 0; i < MAXPROC; i++)
      if (cpu[i] == NULL) {
         cpu[i] = sys_calloc(1, sizeof(proc));
         return i;
      }
   return -1;
}

void freeproc(pid_t pid)
{
   sys_printf("FREEPROC %d nlink %p=%d\n", pid, cpu[pid]->dlnlink, *cpu[pid]->dlnlink);
   if (!pid_is_valid(pid)) {
      return;
   }
   if (!cpu[pid]) {
      return;
   }
   deinit_tls(cpu[pid]);
   (*cpu[pid]->dlnlink)--;
   if (*cpu[pid]->dlnlink <= 0) {
      sys_dlclose(cpu[pid]->dlhndl);
      sys_free(cpu[pid]->dlnlink);
   }   
   if (cpu[pid]->flags & PROC_FORKED || cpu[pid]->flags & PROC_EXECED) {
      freefds(cpu[pid]);
   }
   sys_free(cpu[pid]->cwd);
   freeenv(cpu[pid]->envp);
   free_stack(cpu[pid]->ctx.stack, MAXSTACK);
   sys_free(cpu[pid]);
   cpu[pid] = NULL;
}


pid_t sys_clone(void)
{
   pid_t ret = newproc();
   if (ret == -1) {
      return -1;
   }
   memcpy(cpu[ret], current, sizeof(proc));
   cpu[ret]->flags = PROC_RUNNING | PROC_NEW | PROC_CLONED;
   cpu[ret]->parent = current;
   cpu[ret]->pid = ret;
   cpu[ret]->parentpid = curpid;
   cpu[ret]->cwd = strdup(current->cwd);
   (*current->dlnlink)++;
   cpu[ret]->ctx.stack = alloc_stack(MAXSTACK);
   init_tls(cpu[ret]);
   if (!cpu[ret]->ctx.stack || !cpu[ret]->fds) {
      sys_printf(SYS_ERROR "CLONE alloc stack or fds failed\n");
      freeproc(ret);
      return -1;
   }
   sys_printf(SYS_DEBUG "CLONE newpid=%d in %d(%s), nlink %p=%d flags=%p\n", ret, current->pid, current->argv[0], cpu[ret]->dlnlink, *cpu[ret]->dlnlink, cpu[ret]->flags);
   return ret;
}

pid_t sys_fork(bool_t vfork)
{
   current->forkret = sys_clone();
   sys_printf(SYS_DEBUG "FORK(%d) in %s child=%d fds=%p\n", vfork, current->argv[0], current->forkret, cpu[current->forkret]->fds);
   if (current->forkret == -1) {
      return -1;
   }
   if (!vfork) {
      cpu[current->forkret]->flags |= PROC_FORKED;
   } else
   {
      cpu[current->forkret]->flags |= PROC_VFORKED;
   }
   cpu[current->forkret]->flags &= ~PROC_CLONED;
   cpu[current->forkret]->forkret = 0;
   cpu[current->forkret]->ret = -1;
   switch_context;
   return current->forkret;
}

pid_t sys_waitpid(pid_t pid, int* wstatus, int options)
{
   sys_printf(SYS_DEBUG "WAITPID in %s child=%d\n", current->argv[0], pid);
   if (pid != -1) {
      if (!pid_is_valid(pid) || !cpu[pid]) {
         return -2;
      }
   }   
   *wstatus = 0;
   pid_t child = 0;
   bool_t found = 0;
   while(1) {
      if (pid == -1) {
         int_t i;
         for (i = 0; i < MAXPROC; i++) {
            if (!cpu[i]) {
               continue;
            }
            if (cpu[i]->flags & PROC_DESTROYED) {
               continue;
            }
            if (cpu[i]->parentpid == curpid) {
			      found = 1;	
			      if(cpu[i]->flags & PROC_ENDED) {
                  child = i;
                  goto end;
		         }
            }
         }
      } else {
         if (cpu[pid]->flags & PROC_DESTROYED) {
            return -2;
         }
         found = 1;
         if (cpu[pid]->flags & PROC_ENDED) {
            child = pid;
            goto end;
         }
      }
      if (!found) {
	      return -2;
	   }
      if (options & WNOHANG) {
         return 0; // No child process has exited
      }
      switch_context;
   }
end:
   sys_printf(SYS_DEBUG "WAITPID END pid=%d prog=%s child=%s(%d), flags=%b\n", current->pid, current->argv[0], cpu[child]->argv[0], child, cpu[child]->flags);
   *wstatus = W_EXITCODE(cpu[child]->ret, 0);
   cpu[child]->flags &= ~PROC_RUNNING;
   cpu[child]->flags |= PROC_ENDED;
   cpu[child]->flags |= PROC_DESTROYED;
   return child;
}

void sys_threadend()
{
   sys_printf(SYS_DEBUG "THREADEND pid=%d prog=%s\n", current->pid, current->argv[0]);
   current->flags &= ~PROC_RUNNING;
   current->flags |= PROC_ENDED;
   current->flags |= PROC_DESTROYED;
   switch_context;
}

void sys_atexit(int ret)
{
   sys_printf(SYS_DEBUG "ATEXIT=%d pid=%d prog=%s\n", ret, current->pid, current->argv[0]);
   current->ret = ret;
   current->flags &= ~PROC_RUNNING;
   current->flags |= PROC_ENDED;
   switch_context;
}

