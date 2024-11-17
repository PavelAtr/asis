#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <tiny.h>

int main(int argc, char** argv)
{
    char tmp[10];
    puts("uid=");
    itoa(getuid(), 10, tmp);
    puts(tmp);
    puts(" gid=");
    itoa(getgid(), 10, tmp);
    puts(tmp);
    puts("\n");

    return 0;
}
