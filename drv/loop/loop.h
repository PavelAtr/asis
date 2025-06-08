#ifndef _LOOP_H
#define _LOOP_H
#include "../../core/include/asis.h"
#include <stdarg.h>

typedef struct {
  const char* filename;
  len_t offset;
  len_t pos;
} loop;

len_t loop_read(void* devparam, void* ptr, len_t size);
len_t loop_write(void* devparam, const void* ptr, len_t size);
void loop_seek(void* devparam, len_t offset);
errno_t loop_ioctl(void* devsb, ulong_t request, void* arg1, void* arg2, void* arg3, void* arg4);

#endif
