#!/bin/bash

ROOT=qemu/root

umask 000

CWD=`pwd`

mkdir -p $ROOT/dev
mkdir -p $ROOT/etc
install build/asis.uefi $ROOT/asis.uefi

#cp -ar ./root/* $ROOT/

cd ./root
find . -type d | while read src
do
    mkdir -p $CWD/$ROOT/$src
done
find . -type f | while read src
do
    install $src $CWD/$ROOT/$src
done
find . -type l | while read src
do
    install $src $CWD/$ROOT/$src
done

cd ../
cp /etc/passwd $ROOT/etc/
cp /etc/group $ROOT/etc/

sudo sync
