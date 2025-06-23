#!/bin/sh
set -e


cd ../wlroots
CWD=$(pwd)

export PREFIX=/
export DESTDIR=/home/PavelAtr/asis/root
export CC=cc-asis
export CXX=c++-asis
export SYSROOT="--sysroot=${DESTDIR}"

export CFLAGS="${CFLAGS} ${SYSROOT}"
export LDFLAGS="${LDFLAGS} ${SYSROOT}"
export PKG_CONFIG_LIBDIR="${DESTDIR}${PREFIX}/lib/pkgconfig/"

echo "Building wayland-kms ... "


mkdir -p build

meson setup --cross-file ../scripts/x86_64_asis_meson.txt ./build/ \
--prefix /

ninja -C build/ install





