#include <tinysys.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#ifndef DEBUG
#include "../../userspace/libdl/libdl.h"
#endif

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
   } else {
      int_t ret;
      sys_waitpid(init, &ret, 0);
      if (sys_env[0]) {
         sys_free(sys_env[0]);
      }
      if (sys_env[1]) {
         sys_free(sys_env[1]);
      }
      if (sys_env[2]) {
         sys_free(sys_env[2]);
      }
      return ret;
   }
   return 0;
}

extern AFILE** current_fds;

/*char** dupnullable(char** inargv)
{
	int argc;
	for (argc = 0; inargv[argc]; argc++);
	char** ret = sys_calloc(1, sizeof(char*) * (argc + 1));
	for (argc = 0; inargv[argc]; argc++)
	{
		ret[argc] = strdup(inargv[argc]);
    }
	return ret;
}*/

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

int_t sys_exec(char* file, char** inargv, char** envp)
{
   sys_printf(SYS_DEBUG "EXEC %s\n", file);
   int argc;
   for (argc = 0; inargv[argc]; argc++);
   mountpoint* mount = sys_get_mountpoint(file);
   if (!mount) {
      current->sys_errno = ENOENT;
      current->dlhndl = NULL;
      return -1;
   }
   const char* path = sys_calcpath(mount, file);
   if (!mount->mount_can_execute(mount->sbfs, path, current->uid, current->gid)) {
      current->sys_errno = EPERM;
      current->dlhndl = NULL;
      return -1;
   }
   struct tinystat st;
   if (sys_stat(file, &st) == -1) {
      current->sys_errno = ENOENT;
      current->dlhndl = NULL;
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

   (*current->dlnlink)--;
   
   current->argc = argc;
   current->argv = inargv;// dupnullable(inargv);

   current->dlhndl = sys_dlopen(file, 0);
   if (!current->dlhndl) {
	  sys_printf(SYS_ERROR "EXEC dlopen %s FAILED\n", file);
      current->sys_errno = ENOENT;
      return -1;
   }
   if (current->flags & PROC_CLONED) {
      current->dlnlink = new_dlnlink(current->dlhndl);
      sys_printf(SYS_DEBUG "EXEC dlopen %s nlink %p=%d\n", file, current->dlnlink, *current->dlnlink);
   } else
   {
	   if ((*current->dlnlink) <= 0) {
		   sys_dlclose(current->dlhndl);
      }
   }
   (*current->dlnlink)++;
   sys_printf(SYS_INFO "EXEC dlopen %s nlink %p=%d\n", file, current->dlnlink, *current->dlnlink);
#ifdef DEBUG
   startfunction start = sys_dlsym(current->dlhndl, "_start");
#else
   startfunction start = (void*)(((dlhandle*)current->dlhndl)->obj->dl_elf->hdr->e_entry + 
      ((dlhandle*)current->dlhndl)->obj->dl_elf->exec);
#endif
#ifdef DEBUG
   current->tlsid = sys_dlsym(current->dlhndl, "tinylibc_tls_id");
#endif
   if (current->flags & PROC_CLONED) {
      if (envp) {
		   current->envp = copyenv(envp);
      } else {
		   current->envp = copyenv(((proc*)current->parent)->envp);
      }
   }
   current->fds = cloexecfds(current->fds);
   current_fds = (AFILE**)current->fds;
   current_envp = current->envp;
   current_argv = current->argv;
   sys_dltls(current->dlhndl, curpid);
   
   current->flags &= ~PROC_CLONED;
// MARK   sys_printf(SYS_INFO "freememory=%ld\n", free_memory());
   int ret = start(argc, &current_argv, &current_envp, (void***)&current_fds, &sys_syscall, &sys_atexit);
   switch_context;
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
   current->sys_errno = ENOMEM;
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
   (*cpu[pid]->dlnlink)--;
   if ((*cpu[pid]->dlnlink) <= 0) {
      sys_printf(SYS_DEBUG "FREEPROC DEALLOC %d dlnlink %p=%d\n", pid, cpu[pid]->dlnlink, *cpu[pid]->dlnlink);
      sys_dlclose(cpu[pid]->dlhndl);
      sys_free(cpu[pid]->dlnlink);
   }
   if (!(cpu[pid]->flags & PROC_CLONED)) {
      freeenv(cpu[pid]->envp);
   }
   freefds(cpu[pid]);
   sys_free(cpu[pid]->ctx.stack);
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
   cpu[ret]->ctx.stack = sys_malloc(MAXSTACK);
   cpu[ret]->fds = copyfds(current->fds);
   sys_printf(SYS_DEBUG "CLONE newpid=%d in %d=%s, nlink %p=%d\n", ret, current->pid, current->argv[0], current->dlnlink, *current->dlnlink);
   return ret;
}

pid_t sys_fork()
{
   current->forkret = sys_clone();
   sys_printf(SYS_DEBUG "FORK in %s child=%d\n", current->argv[0], current->forkret);
   if (current->forkret == -1) {
      current->sys_errno = ENOMEM;
      return -1;
   }
   cpu[current->forkret]->forkret = 0;
   cpu[current->forkret]->ret = -1;
   sys_printf(SYS_DEBUG "SWITCH pid=%d prog=%s\n", current->pid, current->argv[0]);
   switch_context;
   sys_printf(SYS_DEBUG "forkret=%d\n", (int)current->forkret);
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
   freeproc(child);
   cpu[child] = NULL;
   return child;
}

void sys_atexit(int ret)
{
   sys_printf(SYS_DEBUG "ATEXIT=%d pid=%d prog=%s\n", ret, current->pid, current->argv[0]);
   current->ret = ret;
   current->flags &= ~PROC_RUNNING;
   current->flags |= PROC_ENDED;
   switch_context;
}

