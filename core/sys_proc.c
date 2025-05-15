#include <tinysys.h>
#include <stdio.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>

#undef fds

proc sys;
char* sys_argv[1] = {"system"};
extern AFILE** current_fds;
char* ld_library_path = "/tinysys/usr/lib:/tinysys/lib";

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
0,
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
  0,
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
  0,
};

int sys_dlnlink = 1;
char* sys_env[4] = {
   "PATH=/tinysys/usr/bin:/tinysys/bin",
   "CWD=/tinysys",
   "UMASK=0022",
   NULL,
};

AFILE* sysfds[COREMAXFD] = {
&sys_stdin,
&sys_stdout,
&sys_stderr,
};

void init_proc()
{
   sys.dlnlink = &sys_dlnlink;
   sys.argv = sys_argv;
   sys.envp = sys_env;
   cpu[0] = &sys;
   current = cpu[0];
   sys.fds = (void**) sysfds;
}

char** copyenv(char*const* e)
{
   char** copy = sys_calloc(1, sizeof(char*) * (COREMAXENV + 1));
   int_t i;
   if (e) {
      for (i = 0; i < COREMAXENV && e[i]; i++) {
         if (e[i][0] == '\0') {
            copy[i] = e[i];
         } else {
            copy[i] = strdup(e[i]);
         }
      }
   }
   for (i = 0; i < COREMAXENV; i++) {
	   if (!copy[i]) {
		   copy[i] = "";
       }
   }
   return copy;
}
void freeenv(char* const* e)
{
   int_t i;
   if (e) {
      for (i = 0; i < COREMAXENV; i++) {
		 if (e[i]) {
            if (e[i][0] != '\0'){
               sys_free(e[i]);
            }
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
    	 ret[i] = sys_calloc(1, sizeof(AFILE));
		 copyfile(ret[i], fds[i]);
      }
   }
   return (void**)ret;
} 

void** cloexecfds(void** infds)
{
   AFILE** fds = (AFILE**)infds;
   int_t i;
   if (infds) {
      for (i = 0; i < COREMAXFD; i++) {
		 if (!fds[i]) {
		    continue;
	     }
	 // MARK

//	 AFILE* dst = fds[i];
//	 if (dst) {
//	    sys_printf("infofile=%p file=%p=%s strbuf=%p pipbuf=%p fd=%d\n", dst, dst->file, dst->file, dst->strbuf, dst->pipbuf, dst->fd);
//     }
     // MARK

         if (fds[i]->flags & O_CLOEXEC) {

             freefile(fds[i]);
			 fds[i] = NULL;
         }
      }
   }
   return infds;
} 

void freefds(proc* task)
{
   AFILE** fds = (AFILE**)task->fds;
   int_t i;
   for (i = 0; i < COREMAXFD; i++) {
	 AFILE* dst = fds[i];
	 // MARK
	 if (dst) {
	    sys_printf("freefile=%p in %s file=%p=%s strbuf=%p pipbuf=%p fd=%d\n", dst, task->argv[0], dst->file, dst->file, dst->strbuf, dst->pipbuf, dst->fd);
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
