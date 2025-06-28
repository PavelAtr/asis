#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <error.h>

#define CHUNK 256

int do_mycat(int argc, char** argv)
{
   if (argc > 1) {
      int input = open(argv[1], O_RDONLY);
      if (input == -1) error(errno, errno, "Error fopen as stdin\n");
      close(0);
      stdin = NULL;
      dup2(input, 0);
      stdin = fdopen(0, "r");
      if (!stdin) error(errno, errno, "Error fdopen stdin\n");
   }
   int i;
   for (i = 0; i < 10; i++)
   {
      if (!afds[i]) continue;

      printf("fd=%d, name=%s\n", i, afds[i]->file);
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