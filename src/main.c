#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	lcd_init(FALSE, 2, 11, 12, 10, 1, 2, 3, 4, 5, 6, 7, 8);

        lcd_swrite("hello world! he");

	while (1) {
	}

	return 0;
}
