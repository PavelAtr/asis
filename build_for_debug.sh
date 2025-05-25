#/bin/sh
set -e

./clean.sh

make -C userspace/alibc install_headers
make -C core -f Makefile.debug install_headers
make -C userspace/libpwd install_headers

make -C userspace/alibc
make -C userspace/alibc install
make -C userspace/libpwd
make -C userspace/libpwd install
make -C userspace/testapp
make -C userspace/testapp install
make -C core -f Makefile.debug
