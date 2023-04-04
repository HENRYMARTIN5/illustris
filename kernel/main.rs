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
use vga::colors::{Color16, TextModeColor};
use vga::writers::{ScreenCharacter, TextWriter, Text80x25};


// Kernel entrypoint (called by arch/<foo>/start.S)
#[no_mangle]
pub fn kmain()
{	
	let text_mode = Text80x25::new();
	let color = TextModeColor::new(Color16::Yellow, Color16::Black);
	let screen_character = ScreenCharacter::new(b'T', color);
	
	text_mode.set_mode();
	text_mode.clear_screen();
	text_mode.write_character(0, 0, screen_character);
	loop {} // If we exit, the machine shuts down - we don't want that, so we loop forever
}

