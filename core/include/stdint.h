#ifndef _STDINT_H
#define _STDINT_H

typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;

#ifndef UEFI
typedef long int64_t;
typedef unsigned long uint64_t;
typedef long long64_t;
typedef unsigned long ulong64_t;
typedef long intptr_t;
typedef unsigned long uintptr_t;
typedef long intmax_t;
typedef unsigned long uintmax_t;
#else
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef long long long64_t;
typedef unsigned long long ulong64_t;
typedef long long intptr_t;
typedef unsigned long long uintptr_t;
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
#endif

#define INT64_C(c)      c ## LL
#define UINT64_C(c)     c ## ULL
#define INTPTR_C(c)     INT32_C(c)
#define UINTPTR_C(c)    UINT32_C(c)
#define PTRDIFF_C(c)    INT32_C(c)


#define INT8_MIN         (-128)
#define INT8_MAX         (127)
#define INT_LEAST8_MIN   INT8_MIN
#define INT_LEAST8_MAX   INT8_MAX
#define INT_FAST8_MIN    INT8_MIN
#define INT_FAST8_MAX    INT8_MAX

#define UINT8_MAX        (255)
#define UINT_LEAST8_MAX  UINT8_MAX
#define UINT_FAST8_MAX   UINT8_MAX

#define INT16_MIN        (-32768)
#define INT16_MAX        (32767)
#define INT_LEAST16_MIN  INT16_MIN
#define INT_LEAST16_MAX  INT16_MAX
#define INT_FAST16_MIN   INT32_MIN
#define INT_FAST16_MAX   INT32_MAX

#define UINT16_MAX       (65535)
#define UINT_LEAST16_MAX UINT16_MAX
#define UINT_FAST16_MAX  UINT32_MAX

#define INT32_MIN        (-2147483647-1)
#define INT32_MAX        (2147483647)
#define INT_LEAST32_MIN  INT32_MIN
#define INT_LEAST32_MAX  INT32_MAX
#define INT_FAST32_MIN   INT32_MIN
#define INT_FAST32_MAX   INT32_MAX

#define UINT32_MAX       (4294967295U)
#define UINT_LEAST32_MAX UINT32_MAX
#define UINT_FAST32_MAX  UINT32_MAX

#define INT64_MIN        (INT64_C(-9223372036854775807)-1)
#define INT64_MAX        (INT64_C(9223372036854775807))
#define INT_LEAST64_MIN  INT64_MIN
#define INT_LEAST64_MAX  INT64_MAX
#define INT_FAST64_MIN   INT64_MIN
#define INT_FAST64_MAX   INT64_MAX
#define UINT64_MAX       (UINT64_C(18446744073709551615))

#endif
