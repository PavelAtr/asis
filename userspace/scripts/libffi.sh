#!/bin/sh
set -e

cd ../libffi-3.4.4
CWD=$(pwd)

export SYSROOT="--sysroot=/asis"
export CFLAGS="${CFLAGS} ${SYSROOT} -D_Nullable= "
export LDFLAGS="${LDFLAGS} ${SYSROOT} -lpwd"
export CC=cc

echo "Building libffi ... "

rm -rf src/*.o
#./configure --host=x86_64-pc-none --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX} --enable-purify-safety
make 
#make install





