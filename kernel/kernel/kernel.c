#include <stdio.h>
#include <kernel/tty.h>
#include <kernel/logging.h>

void kernel_main(void) {
	terminal_initialize();
	info("Hello, kernel World!");
}
