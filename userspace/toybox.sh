#!/bin/sh

cd toybox
CWD=$(pwd)

export CC=gcc
export HOST_CC=gcc
export PREFIX="/tinysys"
export CFLAGS="-g -fPIC -fomit-frame-pointer -Wno-format -D_MSC_VER=2000 -I${PREFIX}/usr/include"
export LDFLAGS="-nostdlib ${PREFIX}/lib/crt.o ${PREFIX}/lib/libc.so"
export TARGET="amd64"
export MK_DIRDEPS_BUILD="yes"

make V=1



