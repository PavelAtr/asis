#!/bin/sh
set -e


cd ../libglvnd-1.6.0
CWD=$(pwd)

export CFLAGS="${CFLAGS} ${SYSROOT}"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib -lac -lathread -ldl"
export PKG_CONFIG_LIBDIR="${DESTDIR}/lib/pkgconfig/"

echo "Building wayland ... "

rm -rf build
mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix=${PREFIX} \


ninja -C build/ install


