#!/bin/bash

ROOT=qemu/root

umask 000

mkdir -p $ROOT/tinysys/bin
mkdir -p $ROOT/tinysys/lib
mkdir -p $ROOT/dev
install core/tinysys.uefi $ROOT/tinysys.uefi

cp -ar /tinysys $ROOT/

touch $ROOT/dev/tty
touch $ROOT/dev/sda
touch $ROOT/dev/loop0
touch $ROOT/dev/fb0

sudo sync
