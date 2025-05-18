#ifdef _LINUX_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
#ifdef _UEFI_
#include <uefi/uefi.h>
#endif

#define STACKSIZE 4096*1024

register char* rsp __asm__("rsp");

char* old_rsp;
char* new_rsp;

int setstack()
{
    old_rsp = rsp;
    printf("Old stack pointer: %p\n", rsp);
    char* stack = (char*)malloc(STACKSIZE);
    if (stack == NULL) {
        fprintf(stderr, "Failed to allocate stack\n");
        exit(-1);
    }
    memset(stack, 0, STACKSIZE);
    rsp = stack + STACKSIZE - 1000; /* Align the stack pointer */
    new_rsp = rsp;
    printf("New stack pointer: %p\n", rsp);
    memcpy(new_rsp, old_rsp, 1000); /* Copy the old stack frame */
    return 0;
}

int main(int argc, char** argv)
{
    char* main_rsp = rsp;
    setstack();
    printf("Stack after function call: %p\n", rsp);
    /* You can now call other functions or run your program logic here.
     For example, you could call a function that uses the new stack. */
    rsp = main_rsp;
    printf("sizeof(long)=%ld\n", sizeof(long));
    return 0;
}