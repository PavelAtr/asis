#include <stdio.h>
#include <string.h>

int i = 0;

FILE *tmpfile(void)
{
    i++;
    char name[32];
    sprintf(name, "/tmp/%i.tmp");
    return fopen(name, "w+");
}