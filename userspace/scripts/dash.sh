#!/bin/sh
set -e

cd ../dash-0.5.12
CWD=$(pwd)

export CFLAGS="${CFLAGS} ${SYSROOT} -D_Nullable= "
export LDFLAGS="${LDFLAGS} ${SYSROOT} -lpwd"
export CC=cc

echo "Building dash ... "

rm -rf src/*.o
./configure --host=x86_64-pc-none --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX}
make 
make install





