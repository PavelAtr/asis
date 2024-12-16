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
typedef unsigned short u_int16_t;
typedef long __off64_t;
typedef long __off_t;
typedef long __int64_t;
#define BUFSIZ 2048
typedef unsigned short u_short;
typedef unsigned long __uintptr_t;
typedef int __nl_item;

#if defined(__cplusplus)
#define __BEGIN_DECLS   extern "C" {
#define __END_DECLS     }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif

#define __format_arg(fmtarg)    __attribute__((__format_arg__ (fmtarg)))

#ifndef __THROW
# if defined __cplusplus
#  define __THROW throw()
# else
#  define __THROW
# endif
#endif



#endif