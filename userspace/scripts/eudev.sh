#!/bin/sh
set -e

cd ../eudev
CWD=$(pwd)

export CFLAGS="${CFLAGS} ${SYSROOT}"
export LDFLAGS="${LDFLAGS} ${SYSROOT}"
export CC=cc

echo $CFLAGS
echo $LDFLAGS

echo "Building eudev ... "

rm -rf src/*.o
#./configure --host=x86_64-pc-none --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX} \
#  --with-sysroot=${PREFIX} \
#  --disable-programs \
#  --disable-blkid \
#  --disable-selinux \
#  --disable-kmod \
#  --disable-mtd_probe
make 
make install





