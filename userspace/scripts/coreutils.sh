#!/bin/sh

cd ../coreutils
CWD=$(pwd)

#./configure
#make

export CFLAGS="${CFLAGS} ${SYSROOT} -D__ASIS__ -DSLOW_BUT_NO_HACKS -D_POSIX_VERSION=202505 -DNL_LOCALE_NAME -DHAVE_IOCTL -include ${CWD}/../scripts/coreutils.h"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -nostdlib -lac"
export LIBS="-lpwd ${PREFIX}/lib/crtstub.a /usr/lib/gcc/x86_64-linux-gnu/12/libgcc.a"

find . -name *.o | xargs rm

./configure --prefix=${PREFIX} --host=x86_64-pc-none  --disable-threads  --disable-acl --disable-assert --disable-rpath \
--disable-libsmack --disable-xattr --disable-libcap -disable-nls --disable-single-binary --disable-dependency-tracking

make
make install
