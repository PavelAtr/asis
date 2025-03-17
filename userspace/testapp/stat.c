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
   printf("%s:\n", path);
   char tmp[10];
   switch (st.st_mode & S_IFMT) {
   case S_IFBLK:
      printf("<BLK> [%d:%d] ", st.st_major, st.st_minor);
      break;
   case S_IFCHR:
      printf("<CHR> [%d:%d] ", st.st_major, st.st_minor);
      break;
   case S_IFDIR:
      printf("%s", "<DIR> ");
      break;
   case S_IFIFO:
      printf("%s", "<FIFO> ");
      break;
   case S_IFLNK:
      printf("%s", "<LNK> ");
      break;
   case S_IFREG:
      printf("%s", "<REG> ");
      break;
   case S_IFSOCK:
      printf("%s", "<SOCK> ");
      break;
   default:
      break;
   }
   printf("uid=%d gid=%d mode=%o size=%ld\n", st.st_uid, 
      st.st_gid, st.st_mode, st.st_size);
   return 0;
}
