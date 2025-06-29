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

void sigquit_handler (int signum)
{
   resetsignals();
   trap_sigquit();
}

void sigstop_handler (int signum)
{
   resetsignals();
   trap_sigstop();
}

void sigcont_handler (int signum)
{
   resetsignals();
   trap_sigcont();
}


void init_hosttrap()
{
   signal(SIGSEGV, segfault_handler);
   signal(SIGQUIT, sigquit_handler);
   signal(SIGSTOP, sigstop_handler);
   signal(SIGCONT, sigcont_handler);
}
