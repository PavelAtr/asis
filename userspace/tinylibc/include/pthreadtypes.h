#ifndef _PTHREADTYPES_H
#define _PTHREADTYPES_H

#define __SIZEOF_PTHREAD_ATTR_T 56

union pthread_attr_t
{
  char __size[__SIZEOF_PTHREAD_ATTR_T];
  long int __align;
};
#ifndef __have_pthread_attr_t
typedef union pthread_attr_t pthread_attr_t;
# define __have_pthread_attr_t 1
#endif


#endif