#ifndef _START_H
#define _START_H

typedef struct {
    int argc;
    int* cerrno;
    char*** cargv;
    char*** cenvp;
    void*** cfds;
    void* syscall_func;
    void* retexit_func;
    char*** cdtv;
} startarg;

#endif