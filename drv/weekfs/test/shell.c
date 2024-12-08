#include <stdio.h>
#include <fcntl.h>
#include <weekfs.h>
#include <unistd.h>
#include <string.h>
#include <weekfs_unix.h>
#include <stdlib.h>


int originfd = -1;
extern sblock* sb;

void help()
{
   printf("help\n");
   printf("new <path>\n");
   printf("find <path>\n");
   printf("origin <rpath>\n");
   printf("unlink <ndentry>\n");
   printf("size <ndentry>\n");
   printf("info <ndentry>\n");
   printf("mknod <path>\n");
   printf("write <path>\n");
   printf("read <path>\n");
   printf("stat <path>\n");
}

void runcommand(char* cmd)
{
   char* param = strchr(cmd, ' ') + 1;
   if (strcmp(cmd, "help") == 0) {
      help();
   }
   if (strstr(cmd, "new ") == cmd) {
      weekfs_dentry* data = calloc(1, sizeof(weekfs_dentry));
      printf("new %s = %s \n", param, strerror(we_dentry_create(sb, param, data)));
      free(data);
   }
   if (strstr(cmd, "alloc ") == cmd) {
      bnum_t parent;
      bnum_t dnt = we_dentry_find(sb, param, &parent);
      printf("alloc %d bnum=%d\n", we_allocate(sb, dnt, 5000), dnt);
   }
   if (strstr(cmd, "trunc ") == cmd) {
      bnum_t parent;
      bnum_t dnt = we_dentry_find(sb, param, &parent);
      printf("trunc %d bnum=%d\n", we_truncate(sb, dnt, 10000), dnt);
   }
   if (strstr(cmd, "find ") == cmd) {
      bnum_t parent;
      printf("%s bnum=%d\n", param, we_dentry_find(sb, param, &parent));
   }
   if (strstr(cmd, "unlink ") == cmd) {
      printf("unlink bnum=%s %s\n", param, strerror(-we_unlink(sb, atoi(param))));
   }
   if (strstr(cmd, "size ") == cmd) {
      bnum_t parent;
      bnum_t dnt = we_dentry_find(sb, param, &parent);
      printf("size bnum=%d is %d\n", dnt, we_calcspace(sb, dnt));
   }
   if (strstr(cmd, "info ") == cmd) {
      hblock temp;
      weekfs_dentry temp_dentry;
      weekfs_getdntry(sb, param, &temp_dentry);
      we_header_load(sb, &temp, temp_dentry.d_dirent.d_ino);
      printf("info bnum=%d type=%d parent=%d next=%d\n", temp_dentry.d_dirent.d_ino,
         temp.type, temp.parent, temp.next);
   }
   if (strstr(cmd, "mknod ") == cmd) {
      printf("mknod %s = %s \n", param, strerror(weekfs_mknod(sb, param, 0, 0,
               S_IRWXU)));
   }
   if (strstr(cmd, "write ") == cmd) {
      if (originfd == -1) {
         return;
      }
      char buf[100000];
      memset(buf, 0x0, 10000);
      lseek(originfd, 0, SEEK_SET);
      len_t len = read(originfd, buf, 10000);
      len_t writed = weekfs_write(sb, param, buf, len, 1124);
      printf("writed %d\n", writed);
   }
   if (strstr(cmd, "read ") == cmd) {
      if (originfd == -1) {
         return;
      }
      char buf[100000];
      memset(buf, 0x0, 100000);
      lseek(originfd, 0, SEEK_SET);
      len_t len = weekfs_read(sb, param, buf, 10000, 1124);
      write(originfd, buf, len);
      printf("readed %d\n", len);
   }
   if (strstr(cmd, "origin ") == cmd) {
      if (originfd > 0) {
         close(originfd);
      }
      originfd = open(param, O_CREAT | O_RDWR, S_IRWXU);
      if (originfd > 0) {
         printf("%s opened\n", param);
      }
   }
}
