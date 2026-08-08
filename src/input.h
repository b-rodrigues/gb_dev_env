#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <gb/gb.h>

extern uint8_t joy_state;
extern uint8_t joy_pressed;

void input_update(void);
uint8_t input_is_down(uint8_t mask);
uint8_t input_is_pressed(uint8_t mask);

#endif /* INPUT_H */
