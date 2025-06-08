#!/bin/sh -e

mkdir root || true
sudo umount root || true
#qemu-system-x86_64 -enable-kvm  -nographic -serial mon:stdio -m 2G -hda hda.img -bios /usr/share/OVMF/OVMF_CODE.fd -net none || true
qemu-system-x86_64 -enable-kvm -m 2G -hda hda.img -bios /usr/share/OVMF/OVMF_CODE.fd -net none || true
sudo mount /dev/loop0 root -o uid=1001,gid=1001
# -nographic -serial mon:stdio