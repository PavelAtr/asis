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
      free_fds(cpu[pid]);
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
      getsp(current->ctx.sp);
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
// MARK setsp(current->ctx.sp);
}
