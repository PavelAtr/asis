#!/bin/sh
set -e


cd ../libinput-1.22.1
CWD=$(pwd)


export CFLAGS="${CFLAGS} ${SYSROOT} -D__BITS_PER_LONG=64"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -lpwd"
export PKG_CONFIG_LIBDIR="/asis/lib/pkgconfig/"

echo "Building libinput ... "

rm -rf build
mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix / \
-Dlibwacom=false \
-Ddebug-gui=false \
-Dtests=false \
-Dinstall-tests=false \
-Depoll-dir=${DESTDIR}${PREFIX}/usr

ninja -C build/ install





