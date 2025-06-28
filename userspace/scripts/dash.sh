#!/bin/sh
set -e

cd ../dash-0.5.12
CWD=$(pwd)


export CC_FOR_BUILD=cc
export CFLAGS="-fPIC -g -fomit-frame-pointer -ftls-model=global-dynamic ${SYSROOT} "
export LDFLAGS=""
export LIBS="-L${DESTDIR}${PREFIX}/lib -lac"

echo "Building dash ... "

rm -rf src/*.o
./configure --host=x86_64-asis-linux --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX}
make V=1
make install





