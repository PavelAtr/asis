#!/bin/sh
set -e

cd ../libgbm
CWD=$(pwd)

export SYSROOT="--sysroot=${DESTDIR}"
export CFLAGS="${CFLAGS} ${SYSROOT} -I${DESTDIR}${PREFIX}/usr/include/libdrm -I${DESTDIR}${PREFIX}/usr/include/libkms -I../wayland-kms/src "
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib -ldl -lkms -ldrm -lwayland-kms"

echo "Building libgbm ..."

./configure --host=x86_64-asis-linux --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX} --includedir=${PREFIX}/usr/include
make 
make install






