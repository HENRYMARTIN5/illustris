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

extern crate vga;
use vga::colors::Color16;
use vga::writers::{Graphics640x480x16, GraphicsWriter};

// Kernel entrypoint (called by arch/<foo>/start.S)
#[no_mangle]
pub fn kmain()
{	
	let mode = Graphics640x480x16::new();
	mode.set_mode();
	mode.clear_screen(Color16::White);
	for (offset, character) in "Hello World!".chars().enumerate() {
		mode.draw_character(270 + offset * 8, 72, character, Color16::Black)
	}
	loop {} // If we exit, the machine shuts down - we don't want that, so we loop forever
}

