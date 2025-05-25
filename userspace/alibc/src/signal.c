#include <signal.h>

/* NOT REALIZED */

sighandler_t signal(int signum, sighandler_t handler)
{
   return handler;
}

int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset)
{
   return 0;
}