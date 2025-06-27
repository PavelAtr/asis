#ifndef _START_H
#define _START_H

typedef struct {
    int argc;
    char** cargv;
    char** cenvp;
    void** cfds;
    void* syscall_func;
    void* retexit_func;
} startarg;

int main(int argc, char** argv);
void libtinyc_init(char** cargv, char** cenviron, void** cfds, void* csyscall, void* cretexit);

#endif
