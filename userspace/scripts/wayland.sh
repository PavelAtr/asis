#!/bin/sh
set -e

cp wayland-scanner.pc ${DESTDIR}/lib/pkgconfig/

cd ../wayland-1.21.0
CWD=$(pwd)

export SYSROOT="--sysroot=${DESTDIR}"
export CFLAGS="${CFLAGS} ${SYSROOT}"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib -lac -lam -lz -llzma -lathread"
export PKG_CONFIG_LIBDIR="${DESTDIR}/lib/pkgconfig/"

echo "Building wayland ... "


rm -rf build
mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix=${PREFIX} \
-Dtests=false \
-Ddocumentation=false

ninja -C build/ install


