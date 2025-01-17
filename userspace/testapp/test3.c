#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
   char temp[1024];
   strcpy(temp, "prefixsuffix");
   int fd = mkostemps(temp, 0, O_RDWR);
   printf("%s=%d\n", temp, fd);
}
