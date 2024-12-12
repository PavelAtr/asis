#!/bin/sh

cd freebsd-src
CWD=$(pwd)

export CC=gcc
export HOST_CC=gcc
export PREFIX="/tinysys"
export CFLAGS="-g -fPIC -fomit-frame-pointer -Wno-format -D__OFF_T_MATCHES_OFF64_T -include ${CWD}/../freebsd-src-stub.h -I${PREFIX}/usr/include"
export LDFLAGS="-nostdlib ${PREFIX}/lib/crt.o ${PREFIX}/lib/libc.so"
export TARGET="amd64"
export MK_DIRDEPS_BUILD="yes"


bmake -m ${CWD}/share/mk -B -C bin/sh

