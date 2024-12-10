#!/bin/sh

export CC=clang
export PREFIX="/tinysys"
export CFLAGS="-g -fPIC -fomit-frame-pointer -Wno-format -D__OFF_T_MATCHES_OFF64_T -I${PREFIX}/usr/include"
export LDFLAGS="-nostdlib ${PREFIX}/lib/crt.o ${PREFIX}/lib/libc.so"
export TARGET="amd64"
export MK_DIRDEPS_BUILD="yes"

cd freebsd-src

CWD=$(pwd)

bmake -m ${CWD}/share/mk -C bin/sh

