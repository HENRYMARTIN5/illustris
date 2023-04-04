#!/bin/bash

echo "This script will compile and install binutils for a specified target."

if [ $# -eq 0 ]; then
    echo "Usage: $0 <target>"
    exit 1
fi

echo "Just double-checking - you wanna build binutils for $1, right? [Y/n]"
read -r answer

if [ "$answer" != "Y" ]; then
    echo "Alright. Come back sometime, alright?"
    exit 1
fi

echo "Cleaning \$HOME/src..."
rm -Rf $HOME/src/*

echo "Installing dependencies..."
sudo apt install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo

export PREFIX="$HOME/opt/cross"
export TARGET=$1
export PATH="$PREFIX/bin:$PATH"

binutils_version=$(ld --version | head -n 1 | cut -d " " -f 7)
binutils_url="https://sourceware.org/pub/binutils/releases/binutils-${binutils_version}.tar.xz"

mkdir -p $HOME/src
pushd $HOME/src
    echo "Downloading packages..."
    wget $binutils_url
    echo "Extracting binutils..."
    unxz "binutils-${binutils_version}.tar.xz"
    tar -xf "binutils-${binutils_version}.tar"
    echo "Building binutils..."
    mkdir -p build-binutils
    pushd build-binutils
        ../binutils-${binutils_version}/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
        make
        make install
    popd
popd

echo "Done. Make sure to add $HOME/opt/cross/bin to your \$PATH"