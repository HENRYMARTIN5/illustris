echo "This script cross-compiles GCC and binutils for the target triplet, passed to this script."
echo "Target: $1"

echo "Cleaning \$HOME/src..."
rm -Rf $HOME/src/*

echo "Installing dependencies..."
sudo apt install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo

export PREFIX="$HOME/opt/cross"
export TARGET=$1
export PATH="$PREFIX/bin:$PATH"

gcc_version=$(gcc --version | head -n 1 | cut -d " " -f 4)
gcc_url="https://ftp.gnu.org/gnu/gcc/gcc-${gcc_version}/gcc-${gcc_version}.tar.xz"
binutils_version=$(ld --version | head -n 1 | cut -d " " -f 7)
binutils_url="https://sourceware.org/pub/binutils/releases/binutils-${binutils_version}.tar.xz"

mkdir -p $HOME/src
pushd $HOME/src
    echo "Downloading packages..."
    wget $gcc_url
    wget $binutils_url
    echo "Extracting gcc..."
    unxz "gcc-${gcc_version}.tar.xz"
    tar -xf "gcc-${gcc_version}.tar"
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
    echo "Building gcc..."
    mkdir -p build-gcc
    pushd build-gcc
        ../gcc-${gcc_version}/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
        make all-gcc
        make all-target-libgcc
        make install-gcc
        make install-target-libgcc
    popd
popd

echo "Done. Make sure to add $HOME/opt/cross/bin to your \$PATH"