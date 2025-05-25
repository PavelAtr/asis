#ifndef _LOCALE_H
#define _LOCALE_H

typedef int locale_t;

char *setlocale(int category, const char *locale);

#define __LC_CTYPE               0
#define __LC_NUMERIC             1
#define __LC_TIME                2
#define __LC_COLLATE             3
#define __LC_MONETARY            4
#define __LC_MESSAGES            5
#define __LC_ALL                 6
#define __LC_PAPER               7
#define __LC_NAME                8
#define __LC_ADDRESS             9
#define __LC_TELEPHONE          10
#define __LC_MEASUREMENT        11
#define __LC_IDENTIFICATION     12

#define LC_CTYPE          __LC_CTYPE
#define LC_NUMERIC        __LC_NUMERIC
#define LC_TIME           __LC_TIME
#define LC_COLLATE        __LC_COLLATE
#define LC_MONETARY       __LC_MONETARY
#define LC_MESSAGES       __LC_MESSAGES
#define LC_ALL            __LC_ALL
#define LC_PAPER          __LC_PAPER
#define LC_NAME           __LC_NAME
#define LC_ADDRESS        __LC_ADDRESS
#define LC_TELEPHONE      __LC_TELEPHONE
#define LC_MEASUREMENT    __LC_MEASUREMENT
#define LC_IDENTIFICATION __LC_IDENTIFICATION

# define LC_CTYPE_MASK          (1 << __LC_CTYPE)
# define LC_NUMERIC_MASK        (1 << __LC_NUMERIC)
# define LC_TIME_MASK           (1 << __LC_TIME)
# define LC_COLLATE_MASK        (1 << __LC_COLLATE)
# define LC_MONETARY_MASK       (1 << __LC_MONETARY)
# define LC_MESSAGES_MASK       (1 << __LC_MESSAGES)
# define LC_PAPER_MASK          (1 << __LC_PAPER)
# define LC_NAME_MASK           (1 << __LC_NAME)
# define LC_ADDRESS_MASK        (1 << __LC_ADDRESS)
# define LC_TELEPHONE_MASK      (1 << __LC_TELEPHONE)
# define LC_MEASUREMENT_MASK    (1 << __LC_MEASUREMENT)
# define LC_IDENTIFICATION_MASK (1 << __LC_IDENTIFICATION)
# define LC_ALL_MASK            (LC_CTYPE_MASK \
                                 | LC_NUMERIC_MASK \
                                 | LC_TIME_MASK \
                                 | LC_COLLATE_MASK \
                                 | LC_MONETARY_MASK \
                                 | LC_MESSAGES_MASK \
                                 | LC_PAPER_MASK \
                                 | LC_NAME_MASK \
                                 | LC_ADDRESS_MASK \
                                 | LC_TELEPHONE_MASK \
                                 | LC_MEASUREMENT_MASK \
                                 | LC_IDENTIFICATION_MASK \
                                 )

#define LC_GLOBAL_LOCALE ((locale_t)-1)

locale_t uselocale(locale_t newloc);
locale_t newlocale(int category_mask, const char *locale,
              locale_t base);


#endif