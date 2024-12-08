#ifndef _FBGOP_H
#define _FBGOP_H

#define MAXMODE 1920 * 1080

typedef struct {
  void* gop;
  unsigned int ramsize;
} fbgop;

int_t fbgop_init(fbgop* devparam);
len_t fbgop_read(void* devparam, void* ptr, len_t size);
len_t fbgop_write(void* devparam, const void* ptr, len_t size);
void fbgop_seek(void* devparam, len_t offset);
int_t fbgop_ioctl(void* devparam, ulong_t request, ...);

#endif
