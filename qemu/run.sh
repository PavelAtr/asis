#!/bin/sh -e

mkdir root || true
sudo umount root || true
qemu-system-x86_64 -enable-kvm -m 2G -hda hda -bios /usr/share/OVMF/OVMF_CODE.fd -net none || true
sudo mount /dev/loop0 root -o uid=1000,gid=1000
