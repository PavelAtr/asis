#include <tinysys.h>
#include "./libdl/libdl.h"
#include <string.h>
#include <errno.h>

proc* cpu[MAXPROC];
int_t curpid = 0;
proc* current;

pid_t newproc()
{
   int_t i;
   for (i = 0; i < MAXPROC; i++)
      if (cpu[i] == NULL) {
         cpu[i] = sys_malloc(sizeof(proc));
         memset(cpu[i], 0x0, sizeof(proc));
         return i;
      }
   *current->sys_errno = ENOMEM;
   return -1;
}

void freeproc(pid_t pid)
{
   if (!pid_is_valid(pid)) {
      return;
   }
   if (!cpu[pid]) {
      return;
   }
   if (!(cpu[pid]->flags & PROC_CLONED)) {
      freefds(cpu[pid]);
      sys_free(cpu[pid]->ctx.stack);
      freeenv(cpu[pid]->envp);
   }
   dlclose(cpu[pid]->dlhandle);
   sys_free(cpu[pid]);
   if (current == cpu[pid]) {
      current = NULL;
   }
   cpu[pid] = NULL;
}

char tempstack[MAXSTACK];
void* tempsp = tempstack + MAXSTACK;

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
   current = cpu[curpid];
   sys_printf("SWITCH at %d newpid=%d parent=%d flags=%d\n",
      prevpid, curpid, current->parentpid, current->flags);
   if (current->flags & PROC_NEW) {
      current->flags &= ~PROC_NEW;
    memcpy(current->ctx.stack, ((proc*)current->parent)->ctx.stack, MAXSTACK);
      size_t stackoff = (char*)((proc*)current->parent)->ctx.stack
         + MAXSTACK - (char*)((proc*)current->parent)->ctx.sp;
      current->ctx.sp = (char*)current->ctx.stack + MAXSTACK - stackoff;
      sys_printf("initcontext %d newstack=%p newsp=%p depth=%ld\n",
         curpid, current->ctx.stack, current->ctx.sp, stackoff);
   }
   sp = current->ctx.sp;
}

int_t sys_setjmp(long_t* env)
{
   env[JMP_STACK] = (long_t)sys_malloc(MAXSTACK);
   env[JMP_SP] = env[JMP_STACK] + (long)((char*)sp - (char*)current->ctx.stack);
   sys_printf("setjmp newstack=%p newsp=%p\n", env[JMP_STACK], env[JMP_SP]);
   memcpy((void*)env[JMP_STACK], current->ctx.stack, MAXSTACK);
   return 0;
}

int_t sys_longjmp(long_t* env)
{
   sys_printf("longjmp newstack=%p newsp=%p\n", env[JMP_STACK], env[JMP_SP]);
   if (current->ctx.stack != (void*)env[JMP_STACK]) {
      sys_free(current->ctx.stack);
   }
   current->ctx.stack = (void*)env[JMP_STACK];
   sp = (void*)env[JMP_SP];
   return 0;
}

