#!/bin/sh
set -e


cd ../wayland-kms
CWD=$(pwd)

export CFLAGS="${CFLAGS} ${SYSROOT} -I${DESTDIR}${PREFIX}/usr/include/libdrm"
export LDFLAGS="${LDFLAGS} ${SYSROOT}"
export PKG_CONFIG_LIBDIR="${DESTDIR}${PREFIX}/lib/pkgconfig/"

echo "Building wayland-kms ... "


mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix /

ninja -C build/ install





