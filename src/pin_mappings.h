/**
 * provides mapping from the arduino uno r3 pins to the at328p processor ports
 */

#ifndef PIN_MAPPINGS_H
#define PIN_MAPPINGS_H

#include <avr/io.h>

#define LED_BUILTIN PB5
#define TX_LED PD5
#define RX_LED PD4

#define ASSERT_VALID_PIN assert_valid_pin

/* returns the port associated with the specified pin
 * returns PB5 which is LED_BUILTIN in case of invalid pin */
uint8_t pport(uint8_t pin); // can I just crash?

// literally crashed if not a valid pin
// I wonder what would happen if I inlined this?
// Does sizeof compute the array or pointer?
void assert_valid_pin(uint8_t pin);

// returns the appropriate data direction register
uint8_t ddrx(uint8_t pin);

#endif // PIN_MAPPINGS_H
