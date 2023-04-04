#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp kernel.amd64.bin isodir/boot/illustris.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "Illustris" {
	multiboot /boot/illustris.kernel
}
EOF
grub-mkrescue -o illustris.iso isodir