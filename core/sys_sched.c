/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <asis.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#undef fds

proc* cpu[MAXPROC];
int_t curpid = 0;
proc* current;
char** current_dtv;
void** current_fds;
errno_t current_errno;
char** current_environ;
char** current_argv;


void switch_task()
{
   if (current) {
      current->ctx.sp = sp;
   }
   pid_t prevpid = curpid;
   if (curpid != 0 && current) {
	   current->envp = current_environ;
   }
   while(1) {
      curpid++;
      if (curpid == MAXPROC) {
         curpid = 1;
      }
      if (!cpu[curpid]) {
         continue;
      }
      if (cpu[curpid]->flags & PROC_ENDED) {
         if (curpid == 1) {
            sys_printf(SYS_ERROR "Task 1 ended!\n");
            curpid = 0;
            break;
         }
      }
      if (cpu[curpid]->flags & PROC_ENDED)
      {
         sys_printf("SCHED FREE %d\n", curpid);
         freeproc(curpid);
         cpu[curpid] = NULL;
         continue;
      }
      break;
   }
   sys_printf(SYS_DEBUG "SWITCH_TASK at %d to %d=%s flags=%b\n",
      prevpid, curpid, cpu[curpid]->argv[0], cpu[curpid]->flags);
   current = cpu[curpid];

   if (current->flags & PROC_NEW) {
      current->flags &= ~PROC_NEW;
      size_t stackoff = ((proc*)current->parent)->ctx.stack
         + MAXSTACK - ((proc*)current->parent)->ctx.sp;
      current->ctx.sp = current->ctx.stack + MAXSTACK - stackoff;
      memcpy(current->ctx.sp, ((proc*)current->parent)->ctx.sp, stackoff);
      sys_printf(SYS_DEBUG "initcontext %d newstack=%p newsp=%p depth=%ld\n",
         curpid, current->ctx.stack, current->ctx.sp, current->ctx.sp - current->ctx.stack);
   }
   current_dtv = current->dtv;
   current_fds = current->fds;
   current_environ = current->envp;
   current_argv = current->argv;
   sp = current->ctx.sp;
}

errno_t sys_setjmp(long_t* env)
{
   env[JMP_SP] = (long_t)sp;
   env[JMP_DEPTH] = current->ctx.stack + MAXSTACK - sp;
   env[JMP_STACK] = (long_t)sys_malloc(env[JMP_DEPTH]);
   memcpy((char*)env[JMP_STACK], sp, env[JMP_DEPTH]);
   sys_printf(SYS_DEBUG "setjmp env=%p sp=%p depth=%ld\n", env, env[JMP_SP], env[JMP_DEPTH]);
   return 0;
}

errno_t sys_longjmp(long_t* env)
{
   if (!env[JMP_STACK])	return 1;
   sys_printf(SYS_DEBUG "longjmp env=%p newsp=%p\n", env, env[JMP_SP]);
   memcpy((char*)env[JMP_SP], (char*)env[JMP_STACK], env[JMP_DEPTH]);
   sp = (char*)env[JMP_SP];
   sys_free((void*)env[JMP_STACK]);
   env[JMP_STACK] = 0;
   return 0;
}

errno_t sys_geterrno()
{
	return current_errno;
}
