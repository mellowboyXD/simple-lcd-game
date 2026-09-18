#include "utils.h"
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

#include "wiring.h"

#define BUTTON_PIN 2
#define OUTPUT_PIN 5

int main()
{
	pin_mode(BUTTON_PIN, INPUT);
	set(BUTTON_PIN, HIGH); // enable internal pull-up resistor

	pin_mode(OUTPUT_PIN, OUTPUT);
	bool_t button_pressed = FALSE;

	while (TRUE) {
		if (debounce(BUTTON_PIN)) {
			if (button_pressed == FALSE) {
				toggle(OUTPUT_PIN);
				button_pressed = TRUE;
			}
		} else {
			button_pressed = FALSE;
		}
	}

	return 0;
}
