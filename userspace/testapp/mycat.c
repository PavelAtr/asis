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
   FILE* console = fopen("/dev/tty", "r+");
   if (argc > 1) {
      int input = open(argv[1], O_RDONLY);
      if (input == -1) err(errno, "Error fopen\n");
      close(0);
      stdin = NULL;
      dup2(input, 0);
      stdin = fdopen(0, "r");
      if (!stdin) err(errno, "Error fdopen\n");
   }
   char buf[CHUNK];
   while (1)
   {
      size_t len, len2;
      while (1)
      {
	      len = fread(buf, 1, CHUNK, stdin);
         if (len != 0) break;
         if (len == 0 && feof(stdin)) return 0;
      }
      while (1)
      {
         len2 = 0;
         len2 += fwrite(buf, 1, len, stdout);
         if (len2 == len) break;
         if (len2 == 0 && feof(stdout)) return 0;
      }
      fprintf(console, "\nmycat: readed %ld:%ld\n", len, len2);
   }
   return 0;
}

int main(int argc, char** argv) {
   do_mycat(argc, argv);
}