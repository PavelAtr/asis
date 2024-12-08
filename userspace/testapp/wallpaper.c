#include <stdlib.h>
#include <stdio.h>
#include <tiny.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAXSIZE 1920 * 1080
int buf[MAXSIZE];

int main(int argc, char** argv)
{
   if (argc < 2) {
      puts("Usage: walpaper <file.raw>\n");
      return -1;
   }
   FILE* pic = fopen(argv[1], "r");
   if (!pic) {
      puts("Error open wallpaper: ");
      puts(strerror(errno));
      puts("\n");
      return -1;
   }
   fseek(pic, 0, SEEK_END);
   int size = ftell(pic);
   fseek(pic, 0, SEEK_SET);
   fread(buf, 1, size, pic);
   FILE* fb = fopen("/dev/fb0", "r+");
   if (!fb) {
      puts("Error open fb: ");
      puts(strerror(errno));
      puts("\n");
      return -1;
   }
   return fwrite(buf, 1, size, fb);
}
