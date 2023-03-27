#include <stdio.h>
#include <kernel/proc.h>
#include <kernel/tty.h>

void test_task() {
	printf("Hello, world!\n");
}

void test_task_2() {
	printf("Hello, second process world!\n");
}

void kernel_main(void) {
	terminal_initialize();
	printf("Creating root proc...");
	int pid = proc_create();
	printf("done\n");
	printf("Creating task...");
	int tid = task_create(pid, &test_task);
	printf("done\n");
	
	printf("Creating second proc...");
	int pid2 = proc_create();
	printf("done\n");
	printf("Creating task...");
	int tid2 = task_create(pid2, &test_task_2);
	printf("done\n");
	
	printf("Forcenext-ing second proc...");
	proc_forcenext(pid2); // Note that running forcenext won't run the proc on the same proc_tick() that it's called from - it puts the process at the very front of the queue for next tick.
	printf("done\n");
	
	printf("Starting main loop...\n");
	while (1) {
		proc_tick();
		// Expected output:
		// Hello, second process world!
		// Hello, world!
	}
}
