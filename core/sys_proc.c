#define malloc(p) sys_malloc(p)
#define free(p) sys_free(p)

#include <tinysys.h>
#include <fcntl.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

proc sys;
prog sysprog;
char* argv[1] = {"system"};
errno_t syserr;

FILE sys_stdin = {
   "/dev/tty",
   100,
   0,
   FILE_INFINITY,
   NULL,
};

FILE sys_stdout = {
   "/dev/tty",
   100,
   0,
   FILE_INFINITY,
   NULL,
};
FILE sys_stderr = {
   "/dev/tty",
   100,
   0,
   FILE_INFINITY,
   NULL,
};

fdesc fdin =    {
	  &sys_stdin,
      0,
      0,
      NULL,
      NULL,
   };

fdesc fdout =    {
	  &sys_stdout, 
      0,
      0,
      NULL,
      NULL,
   };

fdesc fderr =    {
	  &sys_stderr, 
      0,
      0,
      NULL,
      NULL,
   };


fdesc* sysfds[COREMAXFD] = {
&fdin,
&fdout,
&fderr,
};

void init_proc()
{
   sys.program = &sysprog;	
   sys.program->argv = argv;
   cpu[0] = &sys;
   current = cpu[0];
   sys.sys_errno = &syserr;
   sys.program->fds = (void**) sysfds;
}

char** copyenv(char*const* e)
{
   char** copy = sys_malloc(sizeof(char*) * COREMAXENV);
   memset(copy, 0x0, sizeof(char*) * COREMAXENV);
   int_t i;
   for (i = 0; i < COREMAXENV - 2; i++) {
      if (e) {
         if ((e[i])[0] == '\0') {
            copy[i] = e[i];
         } else {
            copy[i] = strdup(e[i]);
         }
      } else {
         copy[i] = "";
      }
   }
   copy[COREMAXENV - 1] = NULL;
   return copy;
}
void freeenv(char*const* e)
{
   int_t i;
   for (i = 0; i < COREMAXENV - 2; i++)
      if ((e[i])[0] != '\0') {
         sys_free(e[i]);
      }
   sys_free((void*)e);
}

void** copyfds(void** infds)
{
   fdesc** fds = (fdesc**)infds;
   fdesc** ret = sys_malloc(sizeof(fdesc*) * COREMAXFD);
   memset(ret, 0x0, sizeof(fdesc*) * COREMAXFD);
   int_t i;
   if (infds) {
      for (i = 0; i < COREMAXFD; i++) {
		 if (!fds[i]) {
		    continue;
	     }
         if (!(fds[i]->flags & O_CLOEXEC)) {
			 ret[i] = malloc(sizeof(fdesc));
			 memset(ret[i], 0x0, sizeof(fdesc));
			 copyfdesc(ret[i], fds[i]);
         }
      }
   }
   return (void**)ret;
} 

void freefds(proc* task)
{
   fdesc** fds = (fdesc**)task->program->fds;
   int_t i;
   for (i = 0; i < COREMAXFD; i++) {
      freefdesc(fds[i]);
   }
   sys_free(fds);
}

int_t sys_setpgid(pid_t pid, pid_t pgid)
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
      *current->sys_errno = EBADR;
      return -1;
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
      *current->sys_errno = EBADR;
      return -1;
   } 
}


