#!/bin/sh
set -e


cd ../mrsh
CWD=$(pwd)

export CFLAGS="${CFLAGS} ${SYSROOT} -Ufds"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -lpwd"
export PKG_CONFIG_LIBDIR="${DESTDIR}/lib/pkgconfig/"

echo "Building mrsh ... "


rm -rf build
mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix=${PREFIX} \

ninja -C build/ install



