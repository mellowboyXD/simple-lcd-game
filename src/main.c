
#include "lcd.h"
#include "utils.h"

#define RS 1
#define RW 2
#define E  3
#define D4 8
#define D5 9
#define D6 10
#define D7 11

int main()
{

        lcd_init(TRUE, 2, RS, RW, E, D4, D5, D6, D7, 0, 0, 0, 0);

        lcd_swrite("hello!");

	while (TRUE) {
	}

	return 0;
}
