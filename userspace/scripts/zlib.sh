#!/bin/sh
set -e

cd ../zlib-1.2.13.dfsg
CWD=$(pwd)

export SYSROOT="--sysroot=${DESTDIR}"
export CFLAGS="${CFLAGS} ${SYSROOT} -DPATH_MAX=4096 "
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib -lac -nostdlib"


echo "Building zlib ... "

rm -rf src/*.o
./configure --prefix=${PREFIX} --includedir=${PREFIX}/usr/include
make 
make install
exit 1





