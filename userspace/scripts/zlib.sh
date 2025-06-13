#!/bin/sh
set -e

cd ../zlib-1.2.13.dfsg
CWD=$(pwd)

export PREFIX="/asis"
export SYSROOT="--sysroot=/asis"
export CFLAGS="${CFLAGS} ${SYSROOT} -DPATH_MAX=4096 "
export LDFLAGS="${LDFLAGS} ${SYSROOT} -lac -nostdlib"
export CC=cc

echo "Building zlib ... "

rm -rf src/*.o
./configure --prefix=${PREFIX} --includedir=${PREFIX}/usr/include
make 
make install






