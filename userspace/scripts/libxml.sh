#!/bin/sh
set -e

cd ../libxml2-2.9.14+dfsg
CWD=$(pwd)

export PREFIX="/asis"
export SYSROOT="--sysroot=/asis"
export CFLAGS="${CFLAGS} ${SYSROOT} -DPATH_MAX=4096 "
export LDFLAGS="${LDFLAGS} ${SYSROOT}"
export CC=cc

echo "Building libxml ... "

rm -rf src/*.o
./configure --host=x86_64-pc-none --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX}
make 
make install






