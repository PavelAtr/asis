#!/bin/sh
set -e

cp wayland-scanner.pc /asis/lib/pkgconfig/

cd ../wayland-1.21.0
CWD=$(pwd)

export SYSROOT="--sysroot=/asis"
export CFLAGS="${CFLAGS} ${SYSROOT} -Ufds"
export LDFLAGS=" ${LDCRT} ${LDFLAGS} ${SYSROOT}"
export CC=cc
export PKG_CONFIG_LIBDIR="/asis/lib/pkgconfig/"
export wayland_scanner=wayland-scanner

echo "Building wayland ... "


rm -rf build
mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix /asis \
-Dtests=false \
-Ddocumentation=false

cd build
meson compile
meson install




