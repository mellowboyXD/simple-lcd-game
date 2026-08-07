#include "wiring.h"
#include <avr/io.h>
#include <util/delay.h>

int main()
{
        const uint8_t pin = 8;
        pin_mode(pin, OUTPUT);

        while(1) {
                set(pin, HIGH);
                _delay_ms(100);

                set(pin, LOW);
                _delay_ms(100);
        }

        return 0;
}

