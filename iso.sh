#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/solus.kernel isodir/boot/solus.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "solus" {
	multiboot /boot/solus.kernel
}
EOF
grub-mkrescue -o solus.iso isodir
