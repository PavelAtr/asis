#!/bin/bash

ROOT=qemu/root

umask 000

mkdir -p $ROOT/tinysys/bin
mkdir -p $ROOT/tinysys/lib
mkdir -p $ROOT/dev
install core/tinysys.efi $ROOT/tinysys.efi
install userspace/shell $ROOT/tinysys/bin/shell
install userspace/hello $ROOT/tinysys/bin/hello
install userspace/ls $ROOT/tinysys/bin/ls
install userspace/stat $ROOT/tinysys/bin/stat
install userspace/wallpaper $ROOT/tinysys/bin/wallpaper
install userspace/wallpaper.raw $ROOT/tinysys/bin/wallpaper.raw
install userspace/tinylibc/libtinyc.so $ROOT/tinysys/lib/libc.so


touch $ROOT/dev/tty
touch $ROOT/dev/sda
touch $ROOT/dev/loop0
touch $ROOT/dev/fb0

