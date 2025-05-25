#/bin/sh
rm -f ./core/syscalls/*.o
rm -f ./core/libdl/x86_64/*.o
rm -f ./core/libdl/*.o
rm -f ./core/libdl/*.o
rm -f ./drv/blk/*.o
rm -f ./drv/loop/*.o
rm -f ./drv/weekfs/src/*.o
rm -f ./drv/uefifs/*.o
rm -f ./drv/fbgop/*.o
rm -f ./drv/tty/*.o
rm -f ./drv/hosttrap/*.o
make -C userspace/alibc clean 
make -C userspace/testapp  clean
make -C userspace/libpwd  clean
make -C userspace/libdl  clean
make -C core -f Makefile.linux clean
make -C posix-uefi/uefi clean

