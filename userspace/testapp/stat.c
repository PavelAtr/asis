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
  if (argc < 2)
    path = "";
  else
    path = argv[1];
  struct stat st;
  if (stat(fullpath(get_current_dir_name(), path), &st)) {
    puts(strerror(errno));
    puts("\n");
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
  puts("uid=");
  itoa(st.st_uid, 10, tmp);
  puts(tmp);
  puts(" gid=");
  itoa(st.st_gid, 10, tmp);
  puts(tmp);
  puts(" mode=");
  itoa(st.st_mode, 8, tmp);
  puts(tmp);
  puts(" size=");
  itoa(st.st_size, 10, tmp);
  puts(tmp);
  puts("\n");
  return 0;
}
