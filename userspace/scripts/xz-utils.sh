#!/bin/sh
set -e

cd ../xz-utils-5.4.1
CWD=$(pwd)

export PREFIX="/asis"
export SYSROOT="--sysroot=/asis"
export CFLAGS="${CFLAGS} ${SYSROOT} -DPATH_MAX=4096 "
export LDFLAGS="${LDFLAGS} ${SYSROOT} -lathread "


echo "Building xz-utils ... "

./configure --host=x86_64-pc-none --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX} --includedir=${PREFIX}/usr/include
make
make install






