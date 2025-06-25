#ifndef _SYS_SYSMACROS_H
#define _SYS_SYSMACROS_H

/** Combines `major` and `minor` into a device number. */
#define makedev(__major, __minor) \
  ( \
    (((__major) & 0xfffff000ULL) << 32) | (((__major) & 0xfffULL) << 8) | \
    (((__minor) & 0xffffff00ULL) << 12) | (((__minor) & 0xffULL)) \
  )

/** Extracts the major part of a device number. */
#define major(__dev) \
  ((unsigned) ((((unsigned long long) (__dev) >> 32) & 0xfffff000) | (((__dev) >> 8) & 0xfff)))

/** Extracts the minor part of a device number. */
#define minor(__dev) \
  ((unsigned) ((((__dev) >> 12) & 0xffffff00) | ((__dev) & 0xff)))



#define gnu_dev_major(dev) major(dev)
#define gnu_dev_minor (dev) minor(dev)
#define gnu_dev_makedev(maj, min) makedev(maj, min)


#endif
