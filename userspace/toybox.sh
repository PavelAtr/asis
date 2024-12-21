#!/bin/sh

cd toybox
CWD=$(pwd)

export CC=clang
export PREFIX="/tinysys"
export CFLAGS="-g -fPIC -fomit-frame-pointer -Wno-format -D_MSC_VER=2000 -U__linux__ -U__GLIBC__ -I${PREFIX}/usr/include -include ${CWD}/../toybox-stub.h"
export LDFLAGS="-nostdlib ${PREFIX}/lib/crt.o ${PREFIX}/lib/libc.so"

make V=1



