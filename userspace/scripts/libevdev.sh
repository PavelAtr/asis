#!/bin/sh
set -e

cd ../libevdev-1.13.0+dfsg
CWD=$(pwd)

export SYSROOT="--sysroot=${DESTDIR}"
export CFLAGS="${CFLAGS} ${SYSROOT}"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib"

echo "Building libevdev ... "

rm -rf src/*.o
./configure --host=x86_64-asis-linux --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX} --includedir=${PREFIX}/usr/include
make 
make install






