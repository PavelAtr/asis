#!/bin/sh
set -e

cd ../libxml2-2.9.14+dfsg
CWD=$(pwd)

export PREFIX="/asis"
export SYSROOT="--sysroot=/asis"
export CFLAGS="${CFLAGS} ${SYSROOT} -DPATH_MAX=4096 "
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${PREFIX}/lib -lathread -lam"

echo "Building libxml ... "

rm -rf src/*.o
./configure --host=x86_64-pc-none --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX} \
--enable-ipv6=no \
--with-http=no \
--with-ftp=no \
--with-python=no

make V=1 
make install






