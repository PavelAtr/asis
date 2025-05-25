#/bin/sh
set -e

./clean.sh

export PREFIX="/tinysys"


make -C userspace/alibc install_headers
make -C userspace/libdl install_headers
make -C userspace/libpwd install_headers
make -C core -f Makefile.linux install_headers

export CFLAGS="-g -fPIC -fomit-frame-pointer --sysroot=${PREFIX} -DUEFI_KERNEL"
make -C userspace/alibc 
make -C userspace/alibc install
make -C userspace/testapp
make -C userspace/testapp install
make -C userspace/libpwd
make -C userspace/libpwd install

unset CFLAGS
make -C core -f Makefile.uefi
