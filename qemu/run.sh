#!/bin/sh -e

mkdir root || true
sudo umount root || true
qemu-system-x86_64 -nographic -serial mon:stdio -enable-kvm -m 2G -hda hda.img -bios /usr/share/OVMF/OVMF_CODE.fd -net none || true
sudo mount /dev/loop0 root -o uid=1001,gid=1001
