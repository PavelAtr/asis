#!/bin/sh
set -e


cd ../wayland-protocols-1.31/
CWD=$(pwd)

export SYSROOT="--sysroot=/asis"
export CFLAGS="${CFLAGS} ${SYSROOT} -Ufds"
export LDFLAGS=" ${LDCRT} ${LDFLAGS} ${SYSROOT}"
export PKG_CONFIG_LIBDIR="/asis/lib/pkgconfig/"

echo "Building wayland-protocols ... "


rm -rf build
mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix /asis \
-Dtests=false

cd build
meson compile
meson install




