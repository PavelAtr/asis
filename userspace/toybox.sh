#!/bin/sh

cd toybox
CWD=$(pwd)

export CC=gcc
export PREFIX="/tinysys"
export CFLAGS="-g -fPIC -fomit-frame-pointer -Wno-format -D_MSC_VER=2000 -U__linux__ -U__GLIBC__ --sysroot=/tinysys -include ${CWD}/../toybox-stub.h"
export LDFLAGS="-nostdlib  --sysroot=/tinysys ${PREFIX}/lib/crt.o ${PREFIX}/lib/tls.a -lpwd -ltinyc -shared"

make clean
make V=1
install generated/unstripped/toybox ${PREFIX}/bin/toybox

cd ${PREFIX}/bin
rm -f sh grep cat
ln toybox sh
ln toybox grep
ln toybox cat

