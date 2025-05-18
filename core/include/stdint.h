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

#endif
