#!/bin/bash

ROOT=qemu/root

umask 000

mkdir -p $ROOT/asis/bin
mkdir -p $ROOT/asis/lib
mkdir -p $ROOT/dev
install core/asis.uefi $ROOT/asis.uefi

cp -ar /asis $ROOT/

touch $ROOT/dev/tty
touch $ROOT/dev/sda
touch $ROOT/dev/loop0
touch $ROOT/dev/fb0

sudo sync
