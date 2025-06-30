#!/bin/sh
set -e

cd ../eudev
CWD=$(pwd)

export CFLAGS="${CFLAGS} -I${DESTDIR}${PREFIX}/usr/include_compat"
export LDFLAGS="${LDFLAGS} ${SYSROOT} -L${DESTDIR}${PREFIX}/lib"


echo "Building eudev ... "

rm -rf src/*.o
./configure --host=x86_64-asis-linux --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX} --includedir=${PREFIX}/usr/include \
  --with-sysroot=${PREFIX} \
  --disable-programs \
  --disable-blkid \
  --disable-selinux \
  --disable-kmod \
  --disable-mtd_probe
make 
make install






