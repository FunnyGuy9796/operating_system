#!/bin/bash
make &&
if grub2-file --is-x86-multiboot os.bin; then
    echo multiboot confirmed
else
    echo the file is not multiboot
fi &&
cp os.bin isodir/boot/os.bin &&
cp grub.cfg isodir/boot/grub/grub.cfg &&
grub2-mkrescue -o os.iso isodir &&
qemu-system-i386 -kernel os.bin