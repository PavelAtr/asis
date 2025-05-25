#!/bin/sh

cd coreutils
CWD=$(pwd)

export PREFIX="/asis"
export CFLAGS="-g -fPIC -fomit-frame-pointer --sysroot=${PREFIX} -DSLOW_BUT_NO_HACKS=1 -D__ASIS__=1"
export LDFLAGS="-Wl,--no-undefined --sysroot=${PREFIX} -nostdlib  ${PREFIX}/lib/crt.o  ${PREFIX}/lib/tls.a -lac"
export LIBS="-lpwd ${PREFIX}/lib/libgcc.a ${PREFIX}/lib/crtstub.a"

./configure \
--host=x86_64-pc-none \
--build=x86_64-linux-gnu \
--target=x86_64-linux-gnu \
--prefix=${PREFIX} \
--disable-test-workaround \
--disable-threads \
--enable-cross-guesses=conservative \
--disable-acl \
--disable-assert \
--disable-rpath \
--disable-libsmack \
--disable-xattr \
--disable-libcap \
--disable-nls \
--disable-single-binary \
--without-selinux

make
make install
