#include <stdlib.h>
#include <stdio.h>
#include <tiny.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char** argv)
{
   char* path;
   if (argc < 2) {
      path = "";
   } else {
      path = argv[1];
   }
   struct stat st;
   if (stat(path, &st) == -1) {
      printf("%s\n", strerror(errno));
      return -2;
   }
   puts(path);
   puts(":\n");
   char tmp[10];
   switch (st.st_mode & S_IFMT) {
   case S_IFBLK:
      puts("<BLK>");
      itoa(st.st_major, 10, tmp);
      puts(tmp);
      puts(":");
      itoa(st.st_minor, 10, tmp);
      puts(tmp);
      puts(" ");
      break;
   case S_IFCHR:
      puts("<CHR>");
      itoa(st.st_major, 10, tmp);
      puts(tmp);
      puts(":");
      itoa(st.st_minor, 10, tmp);
      puts(tmp);
      puts(" ");
      break;
   case S_IFDIR:
      puts("<DIR> ");
      break;
   case S_IFIFO:
      puts("<FIFO> ");
      break;
   case S_IFLNK:
      puts("<LNK> ");
      break;
   case S_IFREG:
      puts("<REG> ");
      break;
   case S_IFSOCK:
      puts("<SOCK> ");
      break;
   default:
      break;
   }
   printf("uid=%d gid=%d mode=%o size=%ld\n", st.st_uid, 
      st.st_gid, st.st_mode, st.st_size);
   return 0;
}
