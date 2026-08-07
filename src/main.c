#include <avr/io.h>
#include <util/delay.h>

int main()
{
        DDRB |= (1 << PD7);

        while(1) {
                PORTB |= (1 << PD7);
                _delay_ms(100);

                PORTB &= ~(1 << PD7);
                _delay_ms(100);
        }

        return 0;
}

