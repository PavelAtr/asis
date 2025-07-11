#!/bin/sh
set -e


cd ../libxkbcommon-1.5.0
CWD=$(pwd)


export CFLAGS="${CFLAGS} ${SYSROOT}"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib -lpwd -lam -lac -nostdlib"
export PKG_CONFIG_LIBDIR="${DESTDIR}${PREFIX}/lib/pkgconfig/"

echo "Building libxkbcommon ... "

rm -rf build
mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix / \
-Denable-x11=false \
-Denable-docs=false

ninja -C build/ install





