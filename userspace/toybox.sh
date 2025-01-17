#!/bin/sh

cd toybox
CWD=$(pwd)

export CC=gcc
export PREFIX="/tinysys"
export CFLAGS="-g -fPIC -fomit-frame-pointer -Wno-format -D_MSC_VER=2000 -U__linux__ -U__GLIBC__ --sysroot /tinysys -I/tinysys/usr/include_stub -include ${CWD}/../toybox-stub.h"
export LDFLAGS="-nostdlib  --sysroot /tinysys ${PREFIX}/lib/crt.o ${PREFIX}/lib/libc.so  ${PREFIX}/lib/libpwd.so"

OBJ="toybox/toys/pending/sh.c"
DMAIN=""

#make V=1
make install DESTDIR=${PREFIX}/bin
