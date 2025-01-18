#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
   printf("strnlen(0123456789, 5)=%d\n", strnlen("0123456789", 5));
   return 0;
}
