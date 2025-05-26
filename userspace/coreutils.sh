#!/bin/sh

cd coreutils
CWD=$(pwd)

#./configure
#make

export CC=gcc
export PREFIX="/asis"
export CFLAGS="-g -fPIC -fomit-frame-pointer --sysroot=${PREFIX} -DSLOW_BUT_NO_HACKS=1 -D_POSIX_VERSION=202505 -D__ASIS__ -include ${CWD}/../coreutils.h"
export LDFLAGS="-Wl,--no-undefined --sysroot=${PREFIX} -nostdlib  ${PREFIX}/lib/crt.o  ${PREFIX}/lib/tls.o -lac"
export LIBS="-lpwd ${PREFIX}/lib/crtstub.a /usr/lib/gcc/x86_64-linux-gnu/12/libgcc.a"
export LD_LIBRARY_PATH=/asis/lib


./configure --host=x86_64-pc-none --build=x86_64-linux-gnu --target=x86_64-other-gnu --prefix=${PREFIX} --disable-threads --enable-cross-guesses=conservative --disable-acl --disable-assert --disable-rpath \
--disable-libsmack --disable-xattr --disable-libcap -disable-nls --disable-single-binary

make
make install
