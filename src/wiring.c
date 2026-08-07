#include "wiring.h"
#include "pin_mappings.h"
#include <stdint.h>

void pin_mode(uint8_t pin, enum io_mode_t mode)
{
	ASSERT_VALID_PIN;

	// need to figure out the bank mapping
	// i.e., PB5 -> DDRB while PC3 -> DDRC

	uint8_t bit = pin_bit(pin);
	volatile uint8_t *reg = ddrx(pin);

        if (mode == OUTPUT) {
                *reg |= (1 << bit);
        } else {
                *reg &= ~(1 << bit);
        }
}

void set(uint8_t pin, enum voltage_mode_t mode)
{
	ASSERT_VALID_PIN;

        const uint8_t bit = pin_bit(pin);
        volatile uint8_t *port = portx(pin);

        if (mode == HIGH) {
                *port |= (1 << bit);
        } else {
                *port &= ~(1 << bit);
        }
}
