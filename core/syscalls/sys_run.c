#include <asis.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include "../../userspace/alibdl/libdl.h"
#include <start.h>

#undef fds

char* initargv[2];
char* mainsp;
extern char* sys_env[COREMAXENV];

int_t sys_runinit()
{
   current->ctx.stack = mainsp - MAXSTACK;
   sys_printf("sys_runinit: stack=%p sp=%p\n", current->ctx.stack, sp);
   initargv[0] = INIT;
   initargv[1] = NULL;
   pid_t init = sys_fork();
   if (init == 0) {
      sys_exec(initargv[0], initargv, NULL);
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
   for (argc = 0; inargv[argc]; argc++);
   mountpoint* mount = sys_get_mountpoint(file);
   if (!mount) {
      current->dlhndl = NULL;
      return ENOENT;
   }
   const char* path = sys_calcpath(mount, file);
   if (!mount->mount_can_execute(mount->sbfs, path, current->uid, current->gid)) {
      current->dlhndl = NULL;
      return EPERM;
   }
   struct stat st;
   if (sys_stat(file, &st) == -1) {
      current->dlhndl = NULL;
      return ENOENT;
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
   (*current->dlnlink)--;
   
   current->argc = argc;
   current->argv = inargv;
   /* dupnullable(inargv); GARBAGE */

   deinit_tls(current);
   current->dlhndl = sys_dlopen(file, 0);
   if (!current->dlhndl) {
	   sys_printf(SYS_ERROR "EXEC dlopen %s FAILED\n", file);
      return ENOENT;
   }
   if (current->flags & PROC_CLONED) {
      current->dlnlink = new_dlnlink(current->dlhndl);
   } else
   {
	   if ((*current->dlnlink) <= 0) {
		   sys_dlclose(current->dlhndl);
      }
   }
   (*current->dlnlink)++;
   sys_printf("EXEC dlnlink %p=%d\n", current->dlnlink, *current->dlnlink);
   init_tls(current);
   current->start = (void*)(((dlhandle*)current->dlhndl)->obj->dl_elf->hdr->e_entry + 
      ((dlhandle*)current->dlhndl)->obj->dl_elf->exec);
   if (current->flags & PROC_CLONED) {
      if (envp) {
		   current->envp = copyenv(envp);
      } else {
		   current->envp = copyenv(((proc*)current->parent)->envp);
      }
   }
   current->fds = cloexecfds(current->fds);
   current->flags &= ~PROC_CLONED;
   current_fds = current->fds;
   current_dtv = current->dtv;
   current_environ = current->envp;
   current_argv = current->argv;
   startarg arg;
   arg.argc = argc;
   arg.cerrno = &current_errno;
   arg.cargv = &current_argv;
   arg.cenvp =  &current_environ;
   arg.cfds = &current_fds;
   arg.syscall_func = &sys_syscall;
   arg.retexit_func = &sys_atexit;
   arg.cdtv = &current_dtv;
   printf("EXEC START %s argv=%p envp=%p fds=%p syscall=%p retexit=%p dtv=%p\n", 
      file, current->argv, current->envp, current->fds, &sys_syscall, &sys_atexit, current->dtv);
   int ret = sys_runoncpu(current->start, &arg, current, sys_getcpu());
   /* Never reach here */
   sys_printf(SYS_DEBUG "EXEC END (NOTREACHEBLE)\n");
   return  ret;
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
   if (!(cpu[pid]->flags & PROC_CLONED)) {
      freeenv(cpu[pid]->envp);
      freefds(cpu[pid]);
   }
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
   (*current->dlnlink)++;
   cpu[ret]->ctx.stack = alloc_stack(MAXSTACK);
   init_tls(cpu[ret]);
   current_fds = current->fds;
   current_dtv = current->dtv;
   if (!cpu[ret]->ctx.stack || !cpu[ret]->fds) {
      sys_printf(SYS_ERROR "CLONE alloc stack or fds failed\n");
      freeproc(ret);
      return -1;
   }
   sys_printf(SYS_DEBUG "CLONE newpid=%d in %d(%s), nlink %p=%d\n", ret, current->pid, current->argv[0], cpu[ret]->dlnlink, *cpu[ret]->dlnlink);
   return ret;
}

pid_t sys_fork()
{
   current->forkret = sys_clone();
   cpu[current->forkret]->fds = copyfds(current->fds);
   sys_printf(SYS_DEBUG "FORK in %s child=%d\n", current->argv[0], current->forkret);
   if (current->forkret == -1) {
      return -1;
   }
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
   sys_printf(SYS_DEBUG "WAITPID END pid=%d prog=%s child=%s(%d), nlink %p=%d\n", current->pid, current->argv[0], cpu[child]->argv[0], child, cpu[child]->dlnlink, *cpu[child]->dlnlink);
   *wstatus = cpu[child]->ret;
   cpu[child]->flags &= ~PROC_RUNNING;
   cpu[child]->flags |= PROC_ENDED;
   switch_context;
   return child;
}

void sys_threadend()
{
   sys_printf(SYS_DEBUG "THREADEND pid=%d prog=%s\n", current->pid, current->argv[0]);
   pid_t pid = current->pid;
   current->flags &= ~PROC_RUNNING;
   current->flags |= PROC_ENDED;
   switch_context;
}

__attribute__((sysv_abi)) 
void sys_atexit(int ret)
{
   sys_printf(SYS_DEBUG "ATEXIT=%d pid=%d prog=%s\n", ret, current->pid, current->argv[0]);
   current->ret = ret;
   current->flags &= ~PROC_RUNNING;
   current->flags |= PROC_ENDED;
   switch_context;
}

