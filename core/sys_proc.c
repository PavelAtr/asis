/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <asis.h>
#include <stdio.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>



proc sys;
char* sys_argv[1] = {"system"};
extern void** current_fds;
char* ld_library_path = "/lib:/usr/lib:/libexec";

char lock1, lock2, lock3;

AFILE sys_stdin = {
F_FILE,
0,
0,
0,
&lock1,
1,
"/dev/tty",
"r+",
0,
0,
FILE_INFINITY,
};

AFILE sys_stdout = {
F_FILE,
0,
0,
1,
&lock2,
1,
"/dev/tty",
"r+",
0,
0,
FILE_INFINITY,
};

AFILE sys_stderr = {
F_FILE,
0,
0,
2,
&lock3,
1,
"/dev/tty",
"r+",
0,
0,
FILE_INFINITY,
};

int sys_dlnlink = 10;
char* sys_env[10];

AFILE* sys_fds[COREMAXFD] = {
&sys_stdin,
&sys_stdout,
&sys_stderr,
};

void init_proc()
{
   cpu[0] = &sys;
   maxcpu = MAXCPU;
   sys.memregs = hyperv_calloc(MAXMEMREG, sizeof(memreg));  
   cpus = hyperv_malloc(sizeof(core*) * maxcpu);
   int i;
   for (i = 0; i < maxcpu; i++) {
      cpus[i] = hyperv_calloc(1, sizeof(core));
      cpus[i]->startcycle = 1;
      cpus[i]->currentpid = 0;
   }

   sys_env[0] = strdup("PATH=/bin:/usr/bin");
   sys_env[1] = strdup("CWD=/");
   sys_env[2] = strdup("UMASK=0027");
   sys_env[3] = strdup("PS1=\\$ ");
   sys_env[4] = strdup("PS2=> ");
   sys_env[5] = NULL;
   sys.argv = sys_argv;
   sys.envp = sys_env;
   sys.fds = (void**) sys_fds;
   *sys_stdin.lock = 0;
   *sys_stdout.lock = 0;
   *sys_stderr.lock = 0;
   current->pid = 0;
   current->parentpid = 0;
   current->cwd = strdup("/");
   current->cpunum = 0;
   current->ret = 0;
   current->forkret = 0;
   current->pgid = 0;
   current->uid = 0;
   current->gid = 0;
   current->flags = PROC_RUNNING;
   current->dlhndl = NULL;
   current->dlnlink = &sys_dlnlink;
   current->parent = &sys;
   current->start = NULL;
}

void freeenv(char** e)
{
   if (!e) {
      return;
   }
   int argc;
	for (argc = 0; e[argc]; argc++){
      if (e[argc]) {
         sys_free(e[argc]);
      }
   }
   sys_free(e);
}

void freefds(proc* task)
{
   AFILE** fds = (AFILE**)task->fds;
   int_t i;
   for (i = 0; i < COREMAXFD; i++) {
/*	 AFILE* dst = fds[i];
	 if (dst) {
	    sys_printf("freefile=%p in %s file=%p=%s strbuf=%p pipbuf=%p fd=%d\n", dst, task->argv[0], dst->file, dst->file, dst->strbuf, dst->pipbuf, dst->fd);
         } GARBAGE*/
      freefile(fds[i]);
   }
   sys_free(fds);
}


errno_t sys_setpgid(pid_t pid, pid_t pgid)
{
   pid_t newpgid = (pgid == 0)? current->pid : pgid;
   if (pid == 0) {
      current->pgid = newpgid;
      return 0;
   }
   if (cpu[pid]) {
      cpu[pid]->pgid = newpgid;
      return 0;
   } else {
      return EBADR;
   } 
}
int_t sys_getpgid(pid_t pid)
{
   if (pid == 0) {
      return current->pgid;
   }
   if (cpu[pid]) {
      return cpu[pid]->pgid;
   } else {
      return -1;
   } 
}
