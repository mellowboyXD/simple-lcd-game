
#include "lcd.h"
#include "utils.h"
#include <util/delay.h>

#define RS 1
#define RW 2
#define E 3
#define D4 8
#define D5 9
#define D6 10
#define D7 11

int main()
{
	lcd_init(TRUE, 2, RS, RW, E, D4, D5, D6, D7, 0, 0, 0, 0);

	lcd_swrite("3===D");

	while (TRUE) {
		lcd_set_cursor(5, 0);
		int i;
		for (i = 0; i < 5; i++) {
			lcd_set_cursor(5, 1);
			lcd_write(' ');
			_delay_ms(300);

			lcd_set_cursor(5 + i, 0);
			lcd_write('-');

			if (i == 0) {
				lcd_set_cursor(5, 1);
				lcd_write('`');
			}

			lcd_set_cursor(5 + i, 0);
			_delay_ms(300);
		}
		lcd_set_cursor(5 + i - 1, 1);
		lcd_write(';');

		_delay_ms(300);

		lcd_set_cursor(5, 0);
		for (i = 0; i < 5; i++) {
			lcd_write(' ');
		}
		lcd_set_cursor(5 + i - 1, 1);
		lcd_write(' ');

		_delay_ms(150);
	}

	return 0;
}
