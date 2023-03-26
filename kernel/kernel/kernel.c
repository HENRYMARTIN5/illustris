#include <stdio.h>
#include <kernel/proc.h>
#include <kernel/tty.h>

void test_task(void *arg) {
	printf("Hello, world!");
}

void kernel_main(void) {
	terminal_initialize();
	printf("Creating root proc...");
	int pid = proc_create();
	printf("done\n");
	printf("Creating task...");
	int tid = task_create(pid, &test_task, NULL);
	printf("done\n");
	printf("Starting main loop...")
	while (1) {
		proc_tick();
	}
}
