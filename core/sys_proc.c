#define malloc(s) sys_malloc(s)
#define calloc(n, s) sys_calloc(n, s)
#define free(p) sys_free(p)
#define printf sys_printf

#include <tinysys.h>
#include <stdio.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#undef fds

proc sys;
prog sysprog;
char* argv[1] = {"system"};
extern AFILE** current_fds;

AFILE sys_stdin = {
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

AFILE sys_stdout = {
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

AFILE sys_stderr = {
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

AFILE* sysfds[COREMAXFD] = {
&sys_stdin,
&sys_stdout,
&sys_stderr,
};

void init_proc()
{
   sys.program = &sysprog;
   sys.program->nlink = 1;
   sys.program->argv = argv;
   cpu[0] = &sys;
   current = cpu[0];
   sys.fds = (void**) sysfds;
   current_fds = (AFILE**)sys.fds;
   current_env = NULL;
}

char** copyenv(char*const* e)
{
   char** copy = sys_calloc(1, sizeof(char*) * COREMAXENV + 1);
   int_t i;
   if (e) {
      for (i = 0; i < COREMAXENV && e[i]; i++) {
		 if (!e[i]) {
			 continue;
	     }
         if (e[i][0] == '\0') {
            copy[i] = e[i];
         } else {
  	        size_t len = strlen(e[i]) + 1;
            copy[i] = malloc(len);
            memcpy(copy[i], e[i], len);
         }
      }
   }
   for (i = 0; i < COREMAXENV; i++) {
	   if (!copy[i]) {
		   copy[i] = "";
       }
   }
   copy[COREMAXENV] = NULL;
   return copy;
}
void freeenv(char* const* e)
{
   int_t i;
   if (e) {
      for (i = 0; i < COREMAXENV; i++) {
         if (e[i][0] != '\0'){
            sys_free(e[i]);
         }
      }
      sys_free((void*)e);
   } 
}

void** copyfds(void** infds)
{
   AFILE** fds = (AFILE**)infds;
   AFILE** ret = sys_calloc(1, sizeof(AFILE*) * COREMAXFD);
   int_t i;
   if (infds) {
      for (i = 0; i < COREMAXFD; i++) {
		 if (!fds[i]) {
		    continue;
	     }
         if (!(fds[i]->flags & O_CLOEXEC)) {
			 ret[i] = sys_calloc(1, sizeof(AFILE));
			 copyfile(ret[i], fds[i]);
         }
      }
   }
   return (void**)ret;
} 

void freefds(proc* task)
{
   AFILE** fds = (AFILE**)task->fds;
   int_t i;
   for (i = 0; i < COREMAXFD; i++) {
	 AFILE* dst = fds[i];
	 // MARK
	 if (dst) {
	    sys_printf("freefile=%p file=%p strbuf=%p pipbuf=%p fd=%d\n", dst, dst->file, dst->strbuf, dst->pipbuf, dst->fd);
        sys_printf("freefile=%p name=%s\n", dst, dst->file);
     }
     // MARK
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
      current->sys_errno = EBADR;
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
      current->sys_errno = EBADR;
      return -1;
   } 
}


