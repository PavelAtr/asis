#!/bin/sh
set -e


cd ../wlroots
CWD=$(pwd)

export CFLAGS="${CFLAGS} ${SYSROOT}"
export LDFLAGS="${LDFLAGS} ${SYSROOT}"
export PKG_CONFIG_LIBDIR="${DESTDIR}${PREFIX}/lib/pkgconfig/"

echo "Building wayland-kms ... "


mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix /

ninja -C build/ install





