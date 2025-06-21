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
-Dlibwacom=false \
-Ddebug-gui=false \
-Dtests=false \
-Dinstall-tests=false
#-Depoll-dir=/etc/epoll

#make 
#make install





