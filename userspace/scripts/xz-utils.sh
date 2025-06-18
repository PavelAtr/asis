#!/bin/sh
set -e

cd ../xz-utils-5.4.1
CWD=$(pwd)

export SYSROOT="--sysroot=${DESTDIR}"
export CFLAGS="${CFLAGS} ${SYSROOT} -DPATH_MAX=4096 "
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib -lathread "


echo "Building xz-utils ... "

./configure --host=x86_64-asis-linux --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX} --includedir=${PREFIX}/usr/include
make
make install






