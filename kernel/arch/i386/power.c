#include <kernel/power.h>
#include <stdlib.h>

void power_shutdown() {
    __asm__ __volatile__ (
        "movb $0x80, %%al\n\t"   // ACPI Power Off command
        "outb %%al, $0x64\n\t"   // Send command to keyboard controller
        "movb $0x01, %%al\n\t"   // Power Off parameter
        "outb %%al, $0x60\n\t"   // Send parameter to keyboard controller
        "cli\n\t"                // Disable interrupts
        "hlt\n\t"                // Halt the CPU
        :                        // No outputs
        :                        // No inputs
        : "eax"                  // Clobber the EAX register
    );
}

void power_reboot() {
    __asm__ __volatile__ (
        "movb $0x80, %%al\n\t"   // ACPI Power Off command
        "outb %%al, $0x64\n\t"   // Send command to keyboard controller
        "movb $0x02, %%al\n\t"   // Reboot parameter
        "outb %%al, $0x60\n\t"   // Send parameter to keyboard controller
        "jmp 1f\n\t"             // Jump to next instruction
        "1: cli\n\t"             // Disable interrupts
        "hlt\n\t"                // Halt the CPU
        :                        // No outputs
        :                        // No inputs
        : "eax"                  // Clobber the EAX register
    );
}