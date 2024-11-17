#/bin/sh
set -e

./clean.sh

export PREFIX="/tinysys"
export CFLAGS="-fPIC -I${PREFIX}/usr/include -fomit-frame-pointer -DUEFI_KERNEL"

make -C userspace/tinylibc install_headers
make -C core -f Makefile.linux install_headers

make -C userspace/tinylibc 
make -C userspace/tinylibc install
make -C userspace/testapp
make -C userspace/testapp install
make -C core -f Makefile.uefi
