#include <unistd.h>

/* NOT REALIZED */

int setpgid(pid_t pid, pid_t pgid)
{
   return 0;
}

pid_t getpgid(pid_t pid)
{
   return 1;
}

pid_t getpgrp(void)
{
   return 1;
}