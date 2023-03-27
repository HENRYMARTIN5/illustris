#include <stdint.h>
#include <kernel/io.h>
#include <kernel/keyboard.h>

#define KBD_CTRL_PORT 0x64
#define KBD_DATA_PORT 0x60

static uint8_t keyboard_buffer[256];
static uint8_t keyboard_buffer_head = 0;
static uint8_t keyboard_buffer_tail = 0;

void init_keyboard() {
    // Disable keyboard interrupts
    uint8_t status = inb(KBD_CTRL_PORT);
    status &= ~(1 << 0); // Clear bit 0
    outb(KBD_CTRL_PORT, status);

    // Send the "disable scanning" command
    outb(KBD_DATA_PORT, 0xF5);

    // Read and discard any data in the keyboard buffer
    while (inb(KBD_CTRL_PORT) & 1) {
        inb(KBD_DATA_PORT);
    }

    // Enable keyboard interrupts
    status |= (1 << 0); // Set bit 0
    outb(KBD_CTRL_PORT, status);
}

static void keyboard_handler() {
    uint8_t scan_code = inb(KBD_DATA_PORT);

    // Add the scan code to the buffer
    keyboard_buffer[keyboard_buffer_head] = scan_code;
    keyboard_buffer_head = (keyboard_buffer_head + 1) % 256;
}

void enable_keyboard_interrupts() {
    // Install the keyboard interrupt handler
    set_interrupt_handler(33, keyboard_handler);

    // Enable keyboard interrupts
    uint8_t status = inb(KBD_CTRL_PORT);
    status |= (1 << 0); // Set bit 0
    outb(KBD_CTRL_PORT, status);
}

uint8_t get_next_key_code() {
    if (keyboard_buffer_head == keyboard_buffer_tail) {
        // The keyboard buffer is empty
        return 0;
    }

    uint8_t scan_code = keyboard_buffer[keyboard_buffer_tail];
    keyboard_buffer_tail = (keyboard_buffer_tail + 1) % 256;

    return scan_code;
}
