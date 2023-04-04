#!/bin/bash

echo "This script will compile and install binutils for a specified target."

if [ $# -eq 0 ]; then
    echo "Usage: $0 <target>"
    exit 1
fi

echo "Just double-checking - you wanna build binutils for $1, right? [y/n]"
read -r answer

if [ "$answer" != "y" ]; then
    echo "Alright. Come back sometime, alright?"
    exit 1
fi

echo "Cleaning \$HOME/src..."
rm -Rf $HOME/src/*

echo "Installing dependencies..."

if command -v apt &> /dev/null; then
    sudo apt install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo
elif command -v pacman &> /dev/null; then
    sudo pacman -S --noconfirm base-devel gmp libmpc mpfr
elif command -v emerge &> /dev/null; then
    sudo emerge --ask sys-devel/gcc sys-devel/make sys-devel/bison sys-devel/flex dev-libs/gmp dev-libs/mpc dev-libs/mpfr sys-apps/texinfo
elif command -v dnf &> /dev/null; then
    sudo dnf install gcc gcc-c++ make bison flex gmp-devel libmpc-devel mpfr-devel texinfo
else
    echo "Couldn't find a package manager. Please install the following packages:"
    echo "build-essential (on Ubuntu - contains gcc, make, g++, etc.) bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo"
    exit 1
fi

export PREFIX="$HOME/opt/cross"
export TARGET=$1
export PATH="$PREFIX/bin:$PATH"

# Check if the user is on Ubuntu
if command -v apt &> /dev/null; then
    # Check if the user is on Ubuntu 20.04
    if [ "$(lsb_release -rs)" = "20.04" ]; then
        binutils_version=$(ld --version | head -n 1 | cut -d " " -f 7) # Binutils version format is different as of Ubuntu 20.x
    fi
fi

# If the user is not on Ubuntu 20.x, use the old format
if [ -z "$binutils_version" ]; then
    binutils_version=$(ld --version | head -n 1 | cut -d " " -f 5)
fi

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