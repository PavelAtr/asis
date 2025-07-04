#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <tiny.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>

int main(int argc, char** argv)
{
   char* path;
   if (argc < 2) {
      path = "";
   } else {
      path = argv[1];
   }
   chdir(getenv("PWD"));
   char* dirname = path;
   DIR* dir = opendir(dirname);
   if (!dir) {
      error(errno, errno, "error open dir\n", dirname);
   }
   struct dirent* dent;
   struct stat st;
   int dfd = dirfd(dir);
   while((dent = readdir(dir)) != NULL) {
      fstatat(dfd, dent->d_name, &st, 0);
      switch (st.st_mode & S_IFMT) {
      case S_IFBLK:
         printf("%s", "<BLK>");
         break;
      case S_IFCHR:
         printf("%s", "<CHR>");
         break;
      case S_IFDIR:
         printf("%s", "<DIR>");
         break;
      case S_IFIFO:
         printf("%s", "<FIFO>");
         break;
      case S_IFLNK:
         printf("%s", "<LNK>");
         break;
      case S_IFREG:
         printf("%s", "<REG>");
         break;
      case S_IFSOCK:
         printf("%s", "<SOCK>");
         break;
      default:
         break;
      }
      printf("%s\n", dent->d_name);
   }
   return 0;
}
