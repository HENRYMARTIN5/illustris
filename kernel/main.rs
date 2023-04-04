#![feature(panic_info_message)]	//< Panic handling
#![no_std]	//< Kernels can't use std
#![crate_name="kernel"]

// Macros, need to be loaded before everything else due to how rust parses
#[macro_use]
mod macros;

// Achitecture-specific modules
#[cfg(target_arch="x86_64")] #[path="arch/amd64/mod.rs"]
pub mod arch;
#[cfg(target_arch="x86")] #[path="arch/x86/mod.rs"]
pub mod arch;

// Exception handling (panic)
pub mod unwind;

// Logging code
mod logging;

// Vga buffer
mod vga_buffer;

// Kernel entrypoint (called by arch/<foo>/start.S)
#[no_mangle]
pub fn kmain()
{	
    println!("Hello World!");
	loop {} // If we exit, the machine shuts down - we don't want that, so we loop forever
}

