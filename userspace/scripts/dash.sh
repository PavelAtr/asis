#!/bin/sh
set -e

cd ../dash-0.5.12
CWD=$(pwd)

export CFLAGS="${CFLAGS} ${SYSROOT} -D_Nullable= "
export LDFLAGS="${LDFLAGS} ${SYSROOT} -lpwd"

echo "Building dash ... "

rm -rf src/*.o
./configure --host=x86_64-asis-linux --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX}
make V=1
make install





