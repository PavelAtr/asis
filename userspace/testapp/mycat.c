#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define CHUNK 256
void err(int ret, char* msg)
{
   fprintf(stderr, "%s: %s\n", msg, strerror(ret));
   exit(ret);
}

int do_mycat(int argc, char** argv)
{
   if (argc > 1) {
      int input = open(argv[1], O_RDONLY);
      if (input == -1) err(errno, "Error fopen\n");
      close(0);
      stdin = NULL;
      dup2(input, 0);
      stdin = fdopen(0, "r");
      printf("stdin size=%ld\n", stdin->size);
      if (!stdin) err(errno, "Error fdopen\n");
   }
   char buf[CHUNK];
   while (1)
   {
      size_t len, len2;
      len = freadall(buf, 1, CHUNK, stdin);
      len2 = fwriteall(buf, 1, len, stdout);
      if (feof(stdin)) break;
   }
   return 0;
}

int main(int argc, char** argv) {
   do_mycat(argc, argv);
}