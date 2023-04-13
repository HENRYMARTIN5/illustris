#![no_std]
#![no_main]

extern crate alloc;

use illustris::{print, println};
use illustris::task::{executor::Executor, keyboard, Task};
use bootloader::{entry_point, BootInfo};
use core::panic::PanicInfo;

entry_point!(kernel_main);

fn kernel_main(boot_info: &'static BootInfo) -> ! {
    use illustris::allocator;
    use illustris::memory::{self, BootInfoFrameAllocator};
    use x86_64::VirtAddr;

    println!("----- Welcome to Illustris! -----");
    print!("Initializing core...");
    illustris::init();
    println!("done.");

    print!("Initializing memory...");
    let phys_mem_offset = VirtAddr::new(boot_info.physical_memory_offset);
    let mut mapper = unsafe { memory::init(phys_mem_offset) };
    let mut frame_allocator = unsafe { BootInfoFrameAllocator::init(&boot_info.memory_map) };
    println!("done.");

    print!("Initializing heap...");
    allocator::init_heap(&mut mapper, &mut frame_allocator).expect("Heap initialization failed!");
    println!("done.");

    println!("Initializing executor...");
    let mut executor = Executor::new();
    println!("done.");

    println!("Spawning keyboard task...");
    executor.spawn(Task::new(keyboard::print_keypresses()));
    executor.run();
}

/// This function is called on panic.
#[panic_handler]
fn panic(info: &PanicInfo) -> ! {
    println!("Hello there, unsuspecting user! It seems that you have encountered a kernel panic! If this panic persists, open an issue on the Github repo. For now, though, here's your error message:\n{}", info);
    illustris::hlt_loop();
}

// async fn async_number() -> u32 {
//     42
// }

// async fn example_task() {
//     let number = async_number().await;
//     println!("async number: {}", number);
// }
