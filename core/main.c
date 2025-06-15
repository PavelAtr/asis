#include <asis.h>
#include "../config.h"

#ifdef CONFIG_TTY
#include "../drv/tty/tty.h"
#endif

#ifdef CONFIG_DUMMYBLK
#include "../drv/dummyblk/dummyblk.h"
#endif

#ifdef CONFIG_LOOP
#include "../drv/loop/loop.h"
#endif

#ifdef CONFIG_FBGOP
#include "../drv/fbgop/fbgop.h"
#endif

#ifdef CONFIG_LINTRAP
#include "../drv/lintrap/lintrap.h"
#endif

#ifdef CONFIG_HOSTFS
#include "../drv/hostfs/hostfs.h"
#endif

#ifdef CONFIG_LINUX
#include <stddef.h>
#include <sys/stat.h>
#include <stdio.h>
#endif

#ifdef CONFIG_UEFI
#include "uefi/uefi.h"
#endif

int main(int argc, char** argv)
{
   sys_printf(SYS_INFO "Starting TinySystem\n");
   init_proc();

#ifdef CONFIG_TTY
   devices[0].file = "/dev/tty";
   devices[0].type = S_IFCHR;
   devices[0].devparams = NULL;
   devices[0].dev_read = &tty_read;
   devices[0].dev_write = &tty_write;
   devices[0].dev_seek = &tty_seek;
   devices[0].dev_ioctl = &tty_ioctl;
#endif

#ifdef CONFIG_DUMMYBLK
   devices[1].file = "/dev/sda";
   devices[1].type = S_IFBLK;
   devices[1].devparams = NULL;
   devices[1].dev_read = &blk_read;
   devices[1].dev_write = &blk_write;
   devices[1].dev_seek = &blk_seek;
   devices[1].dev_ioctl = &blk_ioctl;
#endif

#ifdef CONFIG_LOOP
   loop l;
   l.filename = "/home/pavel/проекты/tinysys/drv/weekfs/virtualhda";
   l.offset = 0;
   l.pos = 0;
   devices[2].file = "/dev/loop0";
   devices[2].type = S_IFBLK;
   devices[2].devparams = &l;
   devices[2].dev_read = &loop_read;
   devices[2].dev_write = &loop_write;
   devices[2].dev_seek = &loop_seek;
   devices[2].dev_ioctl = &loop_ioctl;
#endif

#ifdef CONFIG_FBGOP
   fbgop fb;
   devices[3].file = "/dev/fb0";
   devices[3].type = S_IFCHR;
   devices[3].devparams = &fb;
   devices[3].dev_read = &fbgop_read;
   devices[3].dev_write = &fbgop_write;
   devices[3].dev_seek = &fbgop_seek;
   devices[3].dev_ioctl = &fbgop_ioctl;
   fbgop_init(&fb);
#endif

#ifdef CONFIG_LINUX
   if (sys_mount("/dev/sda", "/", "hostfs", "")) {
      sys_printf(SYS_ERROR "Error mount / %d!\n", current_errno);
   }
#endif

#ifdef CONFIG_UEFI
   if (sys_mount("/dev/sda", "/", "uefifs", "")) {
      sys_printf(SYS_ERROR "Error mount /\n");
   }
#endif

sys_mknod("/dev/tty", S_IFCHR | 0660);
sys_mknod("/dev/sda", S_IFBLK | 0660);
sys_mknod("/dev/loop0", S_IFBLK | 0660);
sys_mknod("/dev/fb0", S_IFCHR | 0660);

#ifdef CONFIG_LINTRAP
   init_hosttrap();
#endif

/* GARBAGE */
#ifdef USE_SYMBOLFILE
   FILE* symfile = fopen("dl.txt", "w+");
   fclose(symfile);
#endif
/* ENDGARBAGE */
   sys_printf(SYS_INFO "End init\n");
   mainsp = sp;
   int ret = sys_runinit();
   sp = mainsp;
   sys_printf(SYS_INFO "End runinit ret=%d\n", ret);
   return ret;
}
