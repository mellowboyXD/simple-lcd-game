#include <avr/io.h>
#include <util/delay.h>

static constexpr uint8_t RS = 4;
static constexpr uint8_t E = 6;
static constexpr uint8_t D4 = 11;
static constexpr uint8_t D5 = 10;
static constexpr uint8_t D6 = 9;
static constexpr uint8_t D7 = 8;

void pinMode()
{

}

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

