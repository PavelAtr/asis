#include <signal.h>

/* NOT REALIZED */
int __libc_current_sigrtmax(void)
{
  return SIGHUP;
}

int __libc_current_sigrtmin(void)
{
  return SIGHUP;
}