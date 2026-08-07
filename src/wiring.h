#ifndef WIRING_H
#define WIRING_H

#include <stdint.h>

enum voltage_mode_t { LOW = 0, HIGH = 1 };
enum io_mode_t { INPUT = 0, OUTPUT = 1 };

// set the pin mode
void pinMode(uint8_t pin, enum io_mode_t mode);

// digitalWrite equivalent
void set(uint8_t pin, enum voltage_mode_t mode);

#endif // WIRING_H
