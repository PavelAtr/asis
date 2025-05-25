#!/bin/sh

cd dash
CWD=$(pwd)

#make clean
#./configure
#make

export PREFIX="/asis"
export CFLAGS="-g -fPIC -fomit-frame-pointer --sysroot=/tinysys -D_Nullable= "
export LDFLAGS="-Wl,--no-undefined --sysroot=/tinysys -nostdlib ${PREFIX}/lib/crt.o ${PREFIX}/lib/tls.a -ltinyc"

rm -rf src/*.o
./configure --host=x86_64-pc-none --build=x86_64-linux-gnu --target=x86_64-linux-gnu --disable-test-workaround --prefix=${PREFIX}
make V
make install





