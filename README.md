# Illustris

A hobby OS written in Rust. Currently in a very early stage of development.

## Building

### Prerequisites

- Rust nightly toolchain (tested with `rustc 1.70.0-nightly (cf7ada217 2023-04-03)`)
- The `rust-src` component installed
- The `llvm-tools-preview` component installed
- The `x86_64-unknown-none` target installed
- `bootimage` installed through cargo

If you don't have any of these (or if you're building in a fresh VM, which is what I reccomend), just follow along with the instructions below.

#### Rustup

Install rustup for your current distro. You can find instructions for your distro [here](https://rustup.rs/). Keep in mind that Windows is not officially supported, but *might* work.

#### Rust Nightly

Forcefully install the correct version of the nightly toolchain:

```bash
rustup toolchain install nightly-2023-04-03
rustup default nightly-2023-04-03
```

#### `rust-src`

Install the `rust-src` and `llvm-tools-preview` components:

```bash
rustup component add rust-src
rustup component add llvm-tools-preview
```

#### Rust Target

Install the `x86_64-unknown-none` target:

```bash
rustup target add x86_64-unknown-none
```

#### `bootimage`

Easy-peasy:

```bash
cargo install bootimage
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
- Thanks to [Philipp Oppermann](https://os.phil-opp.com/) for his [blog series](https://os.phil-opp.com/) on writing an OS in Rust which was very helpful as a reference (and as a good place to steal code from)
- And a final thanks for Terry A. Davis and his work on [TempleOS](https://templeos.org/) for inspiring me to start this whole project
