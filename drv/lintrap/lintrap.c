#include "../../core/include/asis.h"
#include "lintrap.h"
#include <signal.h>
#include <stddef.h>

sigset_t ss;

void resetsignals(void)
{
   sigemptyset(&ss);
   sigprocmask(SIG_SETMASK, &ss, NULL);
}

void segfault_handler (int signum)
{
   resetsignals();
   trap_segfault();
}

void init_hosttrap()
{
   signal(SIGSEGV, segfault_handler);
}
