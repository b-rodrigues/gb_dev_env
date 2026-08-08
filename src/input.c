#include "input.h"

uint8_t joy_state = 0;
uint8_t joy_pressed = 0;

static uint8_t joy_prev = 0;

void input_update(void) {
    joy_state = joypad();
    joy_pressed = joy_state & ~joy_prev;
    joy_prev = joy_state;
}

uint8_t input_is_down(uint8_t mask) {
    return (joy_state & mask) != 0;
}

uint8_t input_is_pressed(uint8_t mask) {
    return (joy_pressed & mask) != 0;
}
