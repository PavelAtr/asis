#!/bin/sh

cd ../coreutils-9.1
CWD=$(pwd)

#./configure
#make

export CFLAGS="${CFLAGS} ${SYSROOT} -D__ASIS__ -DSLOW_BUT_NO_HACKS -D_POSIX_VERSION=202505 -include ${CWD}/../scripts/coreutils.h"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -nostdlib -lac"
export LIBS="-lpwd ${PREFIX}/lib/crtstub.a"

find . -name *.o | xargs rm

./configure --prefix=${PREFIX} --host=x86_64-pc-none  --disable-threads  --disable-acl --disable-assert --disable-rpath \
--disable-libsmack --disable-xattr --disable-libcap -disable-nls --disable-single-binary --disable-dependency-tracking

make
make install
