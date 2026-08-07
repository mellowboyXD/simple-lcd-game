#include "wiring.h"
#include "pin_mappings.h"

void pinMode(uint8_t pin, enum io_mode_t mode)
{
        ASSERT_VALID_PIN;

        // need to figure out the bank mapping
        // i.e., PB5 -> DDRB while PC3 -> DDRC

        uint8_t port = pport(pin);

        switch(port) {
                case PB0:
                case PB1:
                case PB2:
        }
}
