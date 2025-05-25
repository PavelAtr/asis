#include <sys/wait.h>

pid_t wait3(int* wstatus, int options, void* rusage)
{
   return  waitpid(-1, wstatus, options);
}
