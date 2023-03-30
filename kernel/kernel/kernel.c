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

	printf("Starting main loop...\n");
	while (1) {
		proc_tick();
	}
}
