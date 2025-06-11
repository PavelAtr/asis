#!/bin/sh
set -e


cd ../libinput-1.22.1
CWD=$(pwd)


export CFLAGS="${CFLAGS} ${SYSROOT}"
export LDFLAGS="${LDFLAGS} ${SYSROOT}"
export CC=cc
export PKG_CONFIG_LIBDIR="/asis/lib/pkgconfig/"

echo "Building libinput ... "

pkg-config --modversion libudev


mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix /asis \
-Dlibwacom=false \
-Ddebug-gui=false \
-Dtests=false \
-Dinstall-tests=false \
-Depoll-dir=/etc/epoll

#make 
#make install





