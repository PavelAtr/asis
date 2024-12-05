#/bin/sh
set -e

./clean.sh

make -C userspace/tinylibc install_headers
make -C core -f Makefile.linux install_headers
make -C userspace/libpwd install_headers

make -C userspace/tinylibc
make -C userspace/tinylibc install
make -C userspace/libpwd
make -C userspace/libpwd install
make -C userspace/testapp
make -C userspace/testapp install
make -C core -f Makefile.linux
