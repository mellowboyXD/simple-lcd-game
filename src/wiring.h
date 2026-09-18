#ifndef WIRING_H
#define WIRING_H

#include <stdint.h>

enum voltage_mode_t { LOW = 0, HIGH = 1 };
enum io_mode_t { INPUT = 0, OUTPUT = 1 };

// set the pin mode
// equivalent to pinMode
void pin_mode(uint8_t pin, enum io_mode_t mode);

// digitalWrite equivalent
void set(uint8_t pin, enum voltage_mode_t mode);

// toggles a pin on and off
void toggle(uint8_t pin);

// provides a basic button utility with a default debounce delay of 1000us
// returns 1 when button is pressed, 0 when not pressed
uint8_t debounce(uint8_t button_pin);

#endif // WIRING_H
