# Illustris

A hobby OS written in Rust. Currently in a very early stage of development.

## Building

### Prerequisites

- Rust nightly toolchain (tested with `rustc 1.70.0-nightly (cf7ada217 2023-04-03)`)
- The `rust-src` component installed
- The `x86_64-unknown-none` target installed
- A working cross-compiler toolchain (technically only binutils is required, but a full toolchain is nice, just in case) for the `x86_64-elf` target

If you don't have any of these (or if you're building in a fresh VM, which is what I reccomend), just follow along with the instructions below.

#### Rustup

Install rustup for your current distro. You can find instructions for your distro [here](https://rustup.rs/). Keep in mind that Windows is NOT SUPPORTED.

#### Rust Nightly

Forcefully install the correct version of the nightly toolchain:

```bash
rustup toolchain install nightly-2023-04-03
rustup default nightly-2023-04-03
```

#### `rust-src`

Install the `rust-src` component:

```bash
rustup component add rust-src
```

#### Rust Target

Install the `x86_64-unknown-none` target:

```bash
rustup target add x86_64-unknown-none
```

#### Cross-Compiling Binutils

A script is included in this repo, based on the excellent instructions [here](https://wiki.osdev.org/GCC_Cross-Compiler#Building_GCC), to build a cross-compiler toolchain for the `x86_64-elf` target. To use it, just run:

```bash
./binutils-cross.sh x86_64-elf
```

### Actually Building

Once you have all the prerequisites installed, you can build the kernel by running:

```bash
./build.sh
```

This will build the kernel and copy it to the current directory. If you want to build the kernel and run it in QEMU, you can run:

```bash
./qemu.sh
```

However, this will require you to have QEMU installed. If you don't, you can install it with your package manager of choice.

You can also build an ISO and boot it on actual hardware with the following commands:

```bash
./iso.sh
```

Keep in mind that you don't have to run `build.sh` before any of these scripts - they automatically rebuild the kernel before running their individual tasks.

## Credits

- Original kernel design based on John Hodge (@thepowersgang)'s [Rust Barebones Kernel](https://github.com/thepowersgang/rust-barebones-kernel) repo
- GNU grub configuration based on the [OSDev Wiki](https://wiki.osdev.org/GRUB_2#GRUB_2_Configuration)
- Thanks to [Philipp Oppermann](https://os.phil-opp.com/) for his [blog series](https://os.phil-opp.com/) on writing an OS in Rust which was very helpful as a reference
- And a final thanks for Terry A. Davis and his work on [TempleOS](https://templeos.org/) for inspiring me to start this whole project
