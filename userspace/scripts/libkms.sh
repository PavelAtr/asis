#!/bin/sh
set -e

cd ../libkms
CWD=$(pwd)

export PREFIX=/
export DESTDIR=/home/PavelAtr/asis/root
export CC=cc-asis
export CXX=c++-asis

export SYSROOT="--sysroot=${DESTDIR}"
export CFLAGS="${CFLAGS} ${SYSROOT} -I${DESTDIR}${PREFIX}/usr/include/libdrm"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib -ldl"

echo "Building libkms ... "

make 
make install






