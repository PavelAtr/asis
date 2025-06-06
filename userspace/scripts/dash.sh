#!/bin/sh

cd ../dash
CWD=$(pwd)

export CFLAGS="${CFLAGS} ${SYSROOT} -D_Nullable= "
export LDFLAGS="${LDFLAGS} ${SYSROOT}"

echo "Building dash ... "

rm -rf src/*.o
./configure --host=x86_64-pc-none --build=x86_64-linux-gnu --target=x86_64-linux-gnu --disable-test-workaround --prefix=${PREFIX}
make 
make install





