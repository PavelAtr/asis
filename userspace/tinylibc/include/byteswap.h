#ifndef _BYTESWAP_H
#define _BYTESWAP_H

#include <sys/types.h>

uint32_t bswap_32(uint32_t x);
uint64_t bswap_64(uint64_t x);

#endif