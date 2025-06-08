#ifndef _FBGOP_H
#define _FBGOP_H

#include "../../core/include/sys/types.h"

#define MAXMODE 1920 * 1080

typedef struct {
  void* gop;
  unsigned int ramsize;
  unsigned int width;
  unsigned int height;
  unsigned int x1;
  unsigned int y1;
  unsigned int x2;
  unsigned int y2;
} fbgop;

int_t fbgop_init(fbgop* devparam);
len_t fbgop_read(void* devparam, void* ptr, len_t size);
len_t fbgop_write(void* devparam, const void* ptr, len_t size);
void fbgop_seek(void* devparam, len_t offset);


int_t fbgop_ioctl(void* devsb, ulong_t request, void* arg1, void* arg2, void* arg3, void* arg4);
#define GETWIDTH 1000
#define GETHEIGHT 1001
#define SETX 1002
#define SETY 1003
#define SETX2 1004
#define SETY2 1005


#endif
