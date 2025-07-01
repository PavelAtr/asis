#include "../../config.h"

#ifdef CONFIG_UEFI
#include "../../core/uefi/uefi.h"
#endif

#ifdef CONFIG_LINUX
#include <stdio.h>
#endif

#include "tty.h"
#include "../../userspace/alibc/include/termios.h"
#include "../../userspace/alibc/include/sys/ioctl.h"


len_t tty_read(void* devsb, void* ptr, len_t size)
{
start:
   int ch = getchar();
#ifdef CONFIG_UEFI
   if (ch == '\r') {
      ch = '\n'; // Convert carriage return to newline
   }
   putchar(ch);
   if (ch == '\b')
   {
      putchar(ch);
      goto start;
   }
#endif
   char c = ch;
   *((char*)ptr) = c;
   return 1;
}

#ifdef CONFIG_LINUX
len_t tty_write(void* devsb, const void* ptr, len_t size)
{
   size_t ret = fwrite(ptr, 1, size, stdout);
   return ret;
}
#endif

#ifdef CONFIG_UEFI
len_t tty_write(void* devsb, const void* ptr, len_t size)
{
    const char* buf = ptr;
    size_t i;
    for (i = 0; i < size; ++i) {
	putchar(buf[i]);
    }
    return size;
}
#endif

void tty_seek(void* devsb, len_t offset)
{
}

errno_t tty_ioctl(void* devsb, ulong_t request, void* arg1, void* arg2, void* arg3, void* arg4)
{
   struct winsize* ws;
   switch(request) {
      case TIOCGWINSZ:
         ws = (struct winsize*)arg1;
         ws->ws_row = 25;
         ws->ws_col = 80;
         ws->ws_xpixel = 640;
         ws->ws_ypixel = 480;
         return 0;
      case TIOCNOTTY:
         /* NOT REALIZED */
         return 0;
      default:
         break;
   }
   return 7; /* ENOTSUP */
}
