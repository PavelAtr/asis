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
#include "../../userspace/alibc/include/errno.h"


len_t tty_read(void* devsb, void* ptr, len_t size)
{
   int ch = getchar();
   *((int*)ptr) = ch;
   return 1;
}

len_t tty_write(void* devsb, const void* ptr, len_t size)
{
   return fwrite(ptr, 1, size, stdout);
}

void tty_seek(void* devsb, len_t offset)
{
}

errno_t tty_ioctl(void* devsb, ulong_t request, va_list vl)
{
   struct winsize* ws;
   switch(request) {
      case TIOCGWINSZ:
         ws = va_arg(vl, struct winsize*);
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
   
   return ENOTSUP;
}
