#!/bin/sh
set -e


cd ../libinput-1.22.1
CWD=$(pwd)


export CXX="c++-asis"
export CFLAGS="${CFLAGS} -I${DESTDIR}${PREFIX}/usr/include_compat -Wno-unused-parameter -D__BITS_PER_LONG=64 -DUINT_MAX=4294967295U -Wno-error"
export CXXFLAGS=${CFLAGS}
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib -lpwd -lam -lac -nostdlib"
export PKG_CONFIG_LIBDIR="${DESTDIR}${PREFIX}/lib/pkgconfig/"

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





