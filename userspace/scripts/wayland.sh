#!/bin/sh
set -e


cd ../wayland-1.21.0
CWD=$(pwd)

export SYSROOT="--sysroot=/asis"
export CFLAGS="${CFLAGS} ${SYSROOT}"
export LDFLAGS="${LDFLAGS} ${SYSROOT}"
export CC=cc
export PKG_CONFIG_LIBDIR="/asis/lib/pkgconfig/"

echo "Building wayland ... "


mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix /asis \
-Dtests=false \
-Ddtd_validation=false

#make 
#make install




