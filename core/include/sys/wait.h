#ifndef _WAIT_H
#define _WAIT_H

pid_t waitpid(pid_t pid, int* wstatus, int options);
pid_t wait(int* wstatus);


#endif