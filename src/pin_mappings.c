#include "pin_mappings.h"
#include "utils.h"

#include <assert.h>
#include <stdint.h>

// Refer to the arduino datasheet
static const uint8_t pinToPortMap[] = {
	PD0, /* D0 / RX */
	PD1, /* D1 / TX */
	PD2, /* D2 */
	PD3, /* D3 */
	PD4, /* D4 */
	PD5, /* D5 */
	PD6, /* D6 */
	PD7, /* D7 */

	PB0, /* D8 */
	PB1, /* ~D9 */
	PB2, /* ~D10 */
	PB3, /* ~D11 */
	PB4, /* D12 */
	PB5, /* D13 / LED_BUILTIN */

	PC0, /* A0 / D14 */
	PC1, /* A1 / D15 */
	PC2, /* A2 / D16 */
	PC3, /* A3 / D17 */
	PC4, /* A4 / D18 / SDA */
	PC5, /* A5 / D19 / SCL */
};

uint8_t pin_bit(uint8_t pin)
{
	ASSERT_VALID_PIN;
	return pinToPortMap[pin];
}

void assert_valid_pin(uint8_t pin)
{
	uint8_t size = ARRAY_SIZE(pinToPortMap);
	if (pin >= size) {
		while (1)
			; // loop forever
	}
}

volatile uint8_t *ddrx(uint8_t pin)
{
	ASSERT_VALID_PIN;

	if (pin < 8)
		return &DDRD;

	if (pin < 14)
		return &DDRB;

	if (pin < 20)
		return &DDRC;

	return NULL;
}

volatile uint8_t *portx(uint8_t pin)
{
	ASSERT_VALID_PIN;

	if (pin < 8)
		return &PORTD;
	if (pin < 14)
		return &PORTB;

	if (pin < 20)
		return &PORTC;

	return NULL;
}
