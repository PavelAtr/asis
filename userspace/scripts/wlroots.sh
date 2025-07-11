#!/bin/sh
set -e


cd ../wlroots
CWD=$(pwd)

export CFLAGS="${CFLAGS} ${SYSROOT} -include ${DESTDIR}${PREFIX}/usr/include/sys/types.h -include ${DESTDIR}${PREFIX}/usr/include/sys/uio.h"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib /usr/lib/gcc/x86_64-linux-gnu/12/libgcc.a"
export PKG_CONFIG_LIBDIR="${DESTDIR}${PREFIX}/lib/pkgconfig/"

echo "Building wlroot ... "


mkdir -p build
rm -rf build/*

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix / \
-Dlogind=disabled \
-Dlibseat=disabled \
-Dxcb-errors=disabled \
-Dxcb-icccm=disabled \
-Dxwayland=disabled \
-Dx11-backend=disabled \
-Dfbdev-backend=enabled \
-Dexamples=false 

ninja -C build/ install




