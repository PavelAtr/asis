#!/bin/sh

cd dash-0.5.12
CWD=$(pwd)

make clean
./configure
make

#export CC=gcc
export PREFIX="/tinysys"
export CFLAGS="-g -fPIC -fomit-frame-pointer --sysroot=/tinysys -D_Nullable= "
export LDFLAGS="-Wl,--no-undefined --sysroot=/tinysys -nostdlib ${PREFIX}/lib/crt.o -ltinyc -shared"

rm -rf src/*.o
./configure --host=x86_64-pc-none --build=x86_64-linux-gnu --target=x86_64-linux-gnu --disable-test-workaround --prefix=${PREFIX}
make V=1
make install




