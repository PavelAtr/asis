#!/bin/sh
set -e

cd ../mtdev-1.1.6
CWD=$(pwd)

export SYSROOT="--sysroot=${DESTDIR}"
export CFLAGS="${CFLAGS} ${SYSROOT} -include ${DESTDIR}${PREFIX}/usr/include/asm/ioctl.h -include ${DESTDIR}${PREFIX}/usr/include/stdlib.h"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib"

echo "Building libffi ... "

rm -rf src/*.o
./configure --host=x86_64-asis-linux --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX} --includedir=${PREFIX}/usr/include
make 
make install






