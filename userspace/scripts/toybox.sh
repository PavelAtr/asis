#!/bin/sh

cd toybox
CWD=$(pwd)

export PREFIX="/tinysys"
export CFLAGS="-g -fPIC -fomit-frame-pointer -Wno-format -D_MSC_VER=2000 -U__linux__ -U__GLIBC__ --sysroot=/tinysys -include ${CWD}/../toybox-stub.h"
export LDFLAGS="-nostdlib  --sysroot=/tinysys -Wl,-no-undefined ${PREFIX}/lib/crt.o ${PREFIX}/lib/tls.a ${CWD}/../toybox-stub.c -lpwd -ltinyc"

make clean
make V=1
install generated/unstripped/toybox ${PREFIX}/bin/toybox

cd ${PREFIX}/bin
rm -f sh grep cat
ln toybox sh
ln toybox grep
ln toybox cat
ln toybox echo
ln toybox la

