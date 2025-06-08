#!/bin/bash

ROOT=qemu/root

umask 000

mkdir -p $ROOT/asis/bin
mkdir -p $ROOT/asis/lib
mkdir -p $ROOT/dev
mkdir -p $ROOT/etc
install build/asis.uefi $ROOT/asis.uefi

cp -ar /asis $ROOT/
cp /etc/passwd $ROOT/etc/
cp /etc/group $ROOT/etc/

touch $ROOT/dev/tty
touch $ROOT/dev/sda
touch $ROOT/dev/loop0
touch $ROOT/dev/fb0

sudo sync
