#include "../../core/include/tinysys.h"
#include "hosttrap.h"
#include <signal.h>
#include <stddef.h>

sigset_t ss;

void segfault_handler (int signum)
{
   sigemptyset(&ss);
   sigprocmask(SIG_SETMASK, &ss, NULL);
   trap_segfault();
}

void init_hosttrap()
{
   signal(SIGSEGV, segfault_handler);
}
