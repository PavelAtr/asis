/******************************************************
*  Author: Pavel V Samsonov 2025
*******************************************************/

#include <asis.h>
#undef printf
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "../config.h"

#undef fds

proc* cpu[MAXPROC];
int_t curpid = 0;
proc* current;
char** current_dtv;
void** current_fds;
errno_t current_errno;
char** current_environ;
char** current_argv;

pid_t sys_getnextpid(pid_t prevpid, int cpunum)
{
   pid_t newpid = prevpid;
   while (1)
   {
      newpid++;
      if (newpid >= MAXPROC) {
         newpid = 1;
      }
      if (!cpu[newpid]) {
         continue;
      }
      if (cpu[newpid]->flags & PROC_DESTROYED && cpu[newpid] != current) {
         freeproc(newpid);
         cpu[newpid] = NULL;
      }
      if (!cpu[newpid]) {
         continue;
      }
      if (cpus[cpunum]->startcycle == newpid) {
         return sys_endcycle(cpunum);
      }
      if (newpid == prevpid) {
         return sys_endcycle(cpunum);
      }
      if (!(cpu[newpid]->flags & PROC_RUNNING)) {
         continue;
      }
      if (cpu[newpid]->cpunum != cpunum) {
         continue;
      }
      break;
   }
   sys_printf("GET NEXTPID prev=%d, cpu=%d newpid=%d\n", prevpid, cpunum, newpid);
   return newpid;
}

int nextcpu;
void switch_task()
{
   if (current) {
      current->ctx.sp = sp;
   }
   pid_t prevpid = curpid;
   if (curpid != 0 && current) {
	   current->envp = current_environ;
   }
   if (prevpid == 0) {
      curpid = 1;
      goto skip;
   }
   if (!cpus[current->cpunum]->startcycle)
      find_startcycle(current->cpunum);
   curpid = sys_getnextpid(current->pid, current->cpunum);
skip:
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
