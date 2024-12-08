#include <weekfs.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include <sys/stat.h>

sblock* sb;

void help();
void runcommand(char* cmd);

counter_t path_cmp(const char* path, const char* part,  counter_t startpart);

int main(int argc, char** argv)
{
   printf("%d\n", path_cmp("/asdf/fgh", "asdfg", 1));
   sb = calloc(1, sizeof(sblock));
   if (argc > 2) {
      BLOCK_DEV = argv[2];
      if (strcmp(argv[1], "-f") == 0) {
         block_open();
         printf("Formatting\n");
         we_superblock_init(sb, &block_seek, &block_read, &block_write);
         struct stat st;
         stat(BLOCK_DEV, &st);
         we_calc_fs(sb, st.st_size, 512);
         we_format(sb);
         printf("bs=%d, bcount=%d type=%s\n", sb->params.bsize, sb->params.bcount,
            sb->params.type);
         return 0;
      }
      if (strcmp(argv[1], "-t") == 0) {
         printf("Mounting\n");
         block_open();
         we_superblock_init(sb, &block_seek, &block_read, &block_write);
         we_superblock_load(sb);
         sb->alloc_start = 0;
         if (strcmp(sb->params.type, WEEK_TYPE) != 0) {
            printf("ERROR! fstype=%s != compile=%s\n", sb->params.type, WEEK_TYPE);
         } else {
            printf("bs=%d, bcount=%d type=%s\n", sb->params.bsize, sb->params.bcount,
               sb->params.type);
         }
         char buf[1000];
         int a;
         int c = 0;
         while (1) {
            printf("> ");
            while((a = getchar()) != '\n') {
               buf[c++] = a;
            }
            buf[c] = '\0';
            c = 0;
            runcommand(buf);
         }
         return 0;
      }
   } else {
      printf("Usage:\n");
      printf("%s [-f|-t] <rawimage>\n", argv[0]);
   }
   return 0;
}
