#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <error.h>
#include "../../drv/fbgop/fbgop.h"
#include <math.h>


int buf[4000000];

int main(int argc, char** argv)
{
   if (argc < 2) {
      puts("Usage: walpaper <file.raw>\n");
      return -1;
   }
   int fbgop = open("/dev/fb0", O_RDWR);
   if (fbgop == -1) error(errno, errno, "Failed open framebuffer.");
   int width, height;
   ioctl(fbgop, GETWIDTH, &width);
   ioctl(fbgop, GETHEIGHT, &height);
   printf("Framebuffer resolution %d x %d\n", width, height);

   FILE* pic = fopen(argv[1], "r");
   if (!pic) {
      puts("Error open wallpaper: ");
      puts(strerror(errno));
      puts("\n");
      return -1;
   }
   fseek(pic, 0, SEEK_END);
   int size = ftell(pic);
/*   int picwidth = sqrt(((size / sizeof(int)) / (4 * 3))) * 4;
   int picheight = sqrt(((size / sizeof(int)) / (4 * 3))) * 3;*/
   int picwidth = 173;
   int picheight = 110;

   printf("Picture resolution %d x %d\n", picwidth, picheight);
   int x1, x2, y1, y2;
   x1 = (width - picwidth) / 2;
   x2 = x1 + picwidth;
   y1 = (height - picheight) /2;
   y2 = y1 + picheight;
   printf("Draw range (%d,%d)-(%d,%d)\n", x1, y1, x2, y2);

   ioctl(fbgop, SETX, (void*)x1);
   ioctl(fbgop, SETY, (void*)y1);
   ioctl(fbgop, SETX2, (void*)x2);
   ioctl(fbgop, SETY2, (void*)y2);


   fseek(pic, 0, SEEK_SET);
   fread(buf, 1, size, pic);
   FILE* fb = fdopen(fbgop, "r+");
   if (!fb) {
      puts("Error open fb: ");
      puts(strerror(errno));
      puts("\n");
      return -1;
   }
   return fwrite(buf, 1, size, fb);
}
