#include <tinysys.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#ifndef DEBUG
#include "libdl/libdl.h"
#endif

#undef fds

proc* cpu[MAXPROC];
int_t curpid = 0;
proc* current;
AFILE** current_fds;
char** current_env;
char** current_argv;
errno_t* current_errno;


void switch_task()
{
  if (current) {
      current->ctx.sp = sp;
   }
   pid_t prevpid = curpid;
   while(1) {
      curpid++;
      if (curpid == MAXPROC) {
         curpid = 1;
      }
      if (!cpu[curpid]) {
         continue;
      }
      if (!(cpu[curpid]->flags & PROC_RUNNING)) {
         if (curpid == 1) {
            sys_printf(SYS_ERROR "Task 1 ended!\n");
            curpid = 0;
            break;
         }
         continue;
      }
      break;
   }
   sys_printf(SYS_DEBUG "SWITCH at pid=%d prog=%s newpid=%d flags=%d\n",
      prevpid, current->program->argv[0] ,curpid, cpu[curpid]->flags);
   current = cpu[curpid];
   current_fds = (AFILE**)current->fds;
   current_env = current->program->envp;
   sys_dltls(current->program->dlhandle, curpid);
//MARK   current_argv = current->program->argv;
   current_errno = &current->sys_errno;
   if (current->flags & PROC_NEW) {
      current->flags &= ~PROC_NEW;
    memcpy(current->ctx.stack, ((proc*)current->parent)->ctx.stack, MAXSTACK);
      size_t stackoff = (char*)((proc*)current->parent)->ctx.stack
         + MAXSTACK - (char*)((proc*)current->parent)->ctx.sp;
      current->ctx.sp = (char*)current->ctx.stack + MAXSTACK - stackoff;
      sys_printf(SYS_DEBUG "initcontext %d newstack=%p newsp=%p depth=%ld\n",
         curpid, current->ctx.stack, current->ctx.sp, stackoff);
   }
   sp = current->ctx.sp;
}

int_t sys_setjmp(long_t* env)
{
   env[JMP_STACK] = (long_t)sys_malloc(MAXSTACK);
   env[JMP_SP] = env[JMP_STACK] + (long)((char*)sp - (char*)current->ctx.stack);
   sys_printf(SYS_DEBUG "setjmp env=%p newstack=%p newsp=%p\n", env, env[JMP_STACK], env[JMP_SP]);
   memcpy((void*)env[JMP_STACK], current->ctx.stack, MAXSTACK);
   return 0;
}

int_t sys_longjmp(long_t* env)
{
   sys_printf(SYS_DEBUG "longjmp newstack=%p newsp=%p\n", env[JMP_STACK], env[JMP_SP]);
   if (current->ctx.stack != (void*)env[JMP_STACK]) {
      sys_free(current->ctx.stack);
   }
   current->ctx.stack = (void*)env[JMP_STACK];
   sp = (void*)env[JMP_SP];
   return 0;
}

