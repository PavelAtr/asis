#define malloc(s) sys_malloc(s)
#define calloc(n, s) sys_calloc(n, s)
#define free(p) sys_free(p)

#include <tinysys.h>
#include <stdio.h>
#include <fcntl.h>
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
   "r+",
  FILE_INFINITY,
  0,
  0,
NULL,
NULL,
};

FILE sys_stdout = {
"/dev/tty",
   100,
   0,
   "r+",
  FILE_INFINITY,
  1,
  0,
NULL,
NULL,
};
FILE sys_stderr = {
"/dev/tty",
   100,
   0,
   "r+",
  FILE_INFINITY,
  2,
  0,
NULL,
NULL,
};


FILE* sysfds[COREMAXFD] = {
&sys_stdin,
&sys_stdout,
&sys_stderr,
};

void init_proc()
{
   sys.program = &sysprog;
   sys.program->argv = argv;
   cpu[0] = &sys;
   current = cpu[0];
   sys.sys_errno = &syserr;
   sys.program->fds = (void**) sysfds;
   current_fds = sys.program->fds;
   current_env = NULL;
}

char** copyenv(char*const* e)
{
   char** copy = sys_calloc(1, sizeof(char*) * COREMAXENV);
   int_t i;
   for (i = 0; i < COREMAXENV - 2; i++) {
      if (e) {
         if ((e[i])[0] == '\0') {
            copy[i] = e[i];
         } else {
  	        size_t len = strlen(e[i]);
            copy[i] = calloc(1, len + 1);
            memcpy(copy[i], e[i], len);
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
   FILE** fds = (FILE**)infds;
   FILE** ret = sys_calloc(1, sizeof(FILE*) * COREMAXFD);
   int_t i;
   if (infds) {
      for (i = 0; i < COREMAXFD; i++) {
		 if (!fds[i]) {
		    continue;
	     }
         if (!(fds[i]->flags & O_CLOEXEC)) {
			 ret[i] = sys_calloc(1, sizeof(FILE));
			 copyfile(ret[i], fds[i]);
         }
      }
   }
   return (void**)ret;
} 

void freefds(proc* task)
{
   FILE** fds = (FILE**)task->program->fds;
   int_t i;
   for (i = 0; i < COREMAXFD; i++) {
      freefile(fds[i]);
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


