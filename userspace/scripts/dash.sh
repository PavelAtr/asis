#!/bin/sh
set -e

cd ../dash-0.5.12
CWD=$(pwd)

export OLDCC=${CC}
export CC=cc
export OLDCCLD=${CCLD}
export CCLD=cc
export OLDLD=${LD}
export LD=cc
export OLDLDFALGS=${LDFLAGS}
export LDFLAGS=""


./configure
cd src
make mkinit mksyntax mknodes mksignames
cd ../

export CC=${OLDCC}
export CCLD=${OLDCCLD}
export LD=${OLDLD}
export CFLAGS="${CFLAGS} ${SYSROOT} -D_Nullable= "
export LDFLAGS="${OLDLDFALGS} ${SYSROOT} -lpwd"

echo "Building dash ... "

rm -rf src/*.o
./configure --host=x86_64-asis-linux --build=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=${PREFIX}
make V=1
make install





