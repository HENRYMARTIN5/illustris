#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

void init_keyboard();
void enable_keyboard_interrupts();
uint8_t get_next_key_code();

#define KBD_LEFT_CTRL   0x1D
#define KBD_LEFT_SHIFT  0x2A
#define KBD_LEFT_ALT    0x38
#define KBD_LEFT_GUI    0x5B
#define KBD_RIGHT_CTRL  0x9D
#define KBD_RIGHT_SHIFT 0x36
#define KBD_RIGHT_ALT   0xB8
#define KBD_RIGHT_GUI   0x5C

#define KBD_CAPS_LOCK   0x3A
#define KBD_NUM_LOCK    0x45
#define KBD_SCROLL_LOCK 0x46

#define KBD_F1  0x3B
#define KBD_F2  0x3C
#define KBD_F3  0x3D
#define KBD_F4  0x3E
#define KBD_F5  0x3F
#define KBD_F6  0x40
#define KBD_F7  0x41
#define KBD_F8  0x42
#define KBD_F9  0x43
#define KBD_F10 0x44
#define KBD_F11 0x57
#define KBD_F12 0x58

/* ASCII characters */
#define KBD_A       0x1E
#define KBD_B       0x30
#define KBD_C       0x2E
#define KBD_D       0x20
#define KBD_E       0x12
#define KBD_F       0x21
#define KBD_G       0x22
#define KBD_H       0x23
#define KBD_I       0x17
#define KBD_J       0x24
#define KBD_K       0x25
#define KBD_L       0x26
#define KBD_M       0x32
#define KBD_N       0x31
#define KBD_O       0x18
#define KBD_P       0x19
#define KBD_Q       0x10
#define KBD_R       0x13
#define KBD_S       0x1F
#define KBD_T       0x14
#define KBD_U       0x16
#define KBD_V       0x2F
#define KBD_W       0x11
#define KBD_X       0x2D
#define KBD_Y       0x15
#define KBD_Z       0x2C

/* Numbers */
#define KBD_0       0x0B
#define KBD_1       0x02
#define KBD_2       0x03
#define KBD_3       0x04
#define KBD_4       0x05
#define KBD_5       0x06
#define KBD_6       0x07
#define KBD_7       0x08
#define KBD_8       0x09
#define KBD_9       0x0A

#endif /* KEYBOARD_H */