#!/bin/sh

cd ../coreutils-9.1
CWD=$(pwd)

#./configure
#make

export CFLAGS="${CFLAGS} ${SYSROOT} -DSLOW_BUT_NO_HACKS=1 -D_POSIX_VERSION=202505 -D__ASIS__ -include ${CWD}/../scripts/coreutils.h"
export LDFLAGS="${LDFLAGS} ${SYSROOT}"
export LIBS="-lpwd ${PREFIX}/lib/crtstub.a /usr/lib/gcc/x86_64-linux-gnu/12/libgcc.a"

find . -name *.o | xargs rm

./configure --host=x86_64-pc-none --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX} --disable-threads --enable-cross-guesses=conservative --disable-acl --disable-assert --disable-rpath \
--disable-libsmack --disable-xattr --disable-libcap -disable-nls --disable-single-binary

make
make install
