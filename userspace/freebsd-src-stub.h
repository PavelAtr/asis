#ifndef _FREEBSD_SRC_STUB_H
#define _FREEBSD_SRC_STUB_H

#include <sys/types.h>

#define MB_CUR_MAX 2
void bzero(void* s, size_t n);

typedef unsigned int u_int;
typedef unsigned char u_char;
typedef unsigned char u_int8_t;
typedef char *          caddr_t;        /* core address */
typedef const char *    c_caddr_t;      /* core address, pointer to const */

struct spacectl_range {
        off_t   r_offset;       /* starting offset */
        off_t   r_len;  /* length */
};

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

#endif