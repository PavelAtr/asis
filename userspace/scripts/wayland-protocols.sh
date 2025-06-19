#!/bin/sh
set -e


cd ../wayland-protocols-1.31/
CWD=$(pwd)

export CFLAGS="${CFLAGS} ${SYSROOT} -Ufds"
export LDFLAGS="${LDFLAGS} ${SYSROOT}"
export PKG_CONFIG_LIBDIR="${DESTDIR}/lib/pkgconfig/"

echo "Building wayland-protocols ... "


rm -rf build
mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix=${PREFIX}\
-Dtests=false

cd build
meson compile
meson install




