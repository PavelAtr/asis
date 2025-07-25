#!/bin/sh
set -e


cd ../wlroots
CWD=$(pwd)

export CFLAGS="${CFLAGS} ${SYSROOT}"
export LDFLAGS="${LDFLAGS} ${SYSROOT}"
export PKG_CONFIG_LIBDIR="${DESTDIR}${PREFIX}/lib/pkgconfig/"

echo "Building wlroot ... "


mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix /
-Dlogind=disabled \
-Dlibseat=disabled \
-Dxcb-errors=disabled \
-Dxcb-icccm=disabled \
-Dxwayland=disabled \
-Dx11-backend=disabled \
-Dfbdev-backend=enabled \
-Dexamples=disabled \

ninja -C build/ install




