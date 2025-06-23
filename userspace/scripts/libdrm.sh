#!/bin/sh
set -e


cd ../libdrm-2.4.114
CWD=$(pwd)

export CFLAGS="${CFLAGS} ${SYSROOT}"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib -lac"
export PKG_CONFIG_LIBDIR="${DESTDIR}/lib/pkgconfig/"

echo "Building wayland ... "

rm -rf build
mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix=${PREFIX} \
-Dradeon=disabled \
-Damdgpu=disabled \
-Dnouveau=disabled \
-Dvmwgfx=disabled \
-Dcairo-tests=disabled \
-Dinstall-test-programs=false \
-Dudev=false \
-Dtests=false




ninja -C build/ install


