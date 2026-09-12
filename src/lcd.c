#include "lcd.h"
#include "utils.h"
#include "wiring.h"
#include <util/delay.h>

static uint8_t rs_pin = 0;
static uint8_t rw_pin = 0;
static uint8_t e_pin = 0;
static uint8_t data_pins[8] = { 0 };

static uint8_t row_offsets[4] = { 0 };

static uint8_t display_function = 0;
static uint8_t display_control = 0;
static uint8_t display_mode = 0;

static uint8_t num_lines = 0;

static void enable_pulse()
{
	set(e_pin, LOW);
	_delay_us(1);
	set(e_pin, HIGH);
	_delay_us(1);
	set(e_pin, LOW);
	_delay_us(100); // commands need >37us to settle
}

static void write_4_bits(uint8_t value)
{
	for (int i = 0; i < 4; i++) {
		set(data_pins[i], (value >> i) & 0x01);
	}

	enable_pulse();
}

static void write_8_bits(uint8_t value)
{
	for (int i = 0; i < 8; i++) {
		set(data_pins[i], (value >> i) & 0x01);
	}

	enable_pulse();
}

static void send(uint8_t value, enum voltage_mode_t mode)
{
	set(rs_pin, mode);

	// set rw pin to low
	set(rw_pin, LOW);

	if (display_function & LCD_8BIT_MODE) {
		write_8_bits(value);
	} else {
		write_4_bits(value >> 4);
		write_4_bits(value);
	}
}

inline static void command(uint8_t value)
{
	send(value, LOW);
}

static void set_row_offsets(uint8_t row0, uint8_t row1, uint8_t row2,
			    uint8_t row3)
{
	row_offsets[0] = row0;
	row_offsets[1] = row1;
	row_offsets[2] = row2;
	row_offsets[3] = row3;
}

static void begin(uint8_t rows, uint8_t cols, uint8_t char_size)
{
	num_lines = rows;

	set_row_offsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);

	pin_mode(rs_pin, OUTPUT);
	pin_mode(rw_pin, OUTPUT);
	pin_mode(e_pin, OUTPUT);

	for (int i = 0; i < ((display_function & LCD_8BIT_MODE) ? 8 : 4); i++) {
		pin_mode(data_pins[i], OUTPUT);
	}

	_delay_us(50000);
	set(rs_pin, LOW);
	set(e_pin, LOW);

	if (display_function & LCD_8BIT_MODE) {
		command(LCD_FUNCTION_SET | display_function);
		_delay_us(50000);

		command(LCD_FUNCTION_SET | display_function);
		_delay_us(200);

		command(LCD_FUNCTION_SET | display_function);
	} else {
		write_4_bits(0x03);
		_delay_us(50000);

		write_4_bits(0x03);
		_delay_us(50000);

		write_4_bits(0x03);
		_delay_us(200);

		write_4_bits(0x20);
	}

	command(LCD_FUNCTION_SET | display_function);

	display_control = LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF;
	lcd_display();

	lcd_clear();

	display_mode = LCD_ENTRY_LEFT | LCD_ENTRY_DECREMENT;
	command(LCD_ENTRY_SET | display_mode);
}

/* Public Functions */

void lcd_init(bool_t four_bit_mode, uint8_t l, uint8_t rs, uint8_t rw,
	      uint8_t e, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
	      uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)
{
	rs_pin = rs;
	rw_pin = rw;
	e_pin = e;

	data_pins[0] = d0;
	data_pins[1] = d1;
	data_pins[2] = d2;
	data_pins[3] = d3;
	data_pins[4] = d4;
	data_pins[5] = d5;
	data_pins[6] = d6;
	data_pins[7] = d7;

	uint8_t lines = (l >= 2) ? LCD_2_LINES_MODE : LCD_1_LINE_MODE;

	if (four_bit_mode == TRUE) {
		display_function = LCD_4BIT_MODE | lines | LCD_5x8_DOTS;
	} else {
		display_function = LCD_8BIT_MODE | lines | LCD_5x8_DOTS;
	}

	uint8_t rows = (l >= 2) ? 2 : 1;
	begin(rows, 16, LCD_5x8_DOTS);
}

void lcd_clear()
{
	command(LCD_CLEAR);
	_delay_us(2000);
}

void lcd_display()
{
	display_control |= LCD_DISPLAY_ON;

	command(LCD_DISPLAY_CONTROL_SET | display_control);
}

void lcd_no_display()
{
	display_control &= ~LCD_DISPLAY_ON;
	command(LCD_DISPLAY_CONTROL_SET | display_control);
}

void lcd_cursor()
{
	display_mode |= LCD_CURSOR_ON;
	command(LCD_ENTRY_SET | display_mode);
}

void lcd_cursor_blink()
{
        display_mode |= LCD_BLINK_ON;
        command(LCD_ENTRY_SET | display_mode);
}

void lcd_no_cursor_blink()
{
        display_mode &= ~LCD_BLINK_ON;
        command(LCD_ENTRY_SET | display_mode);
}

void lcd_no_cursor()
{
        display_mode &= ~LCD_CURSOR_OFF;
        command(LCD_ENTRY_SET | display_mode);
}

void lcd_write(uint8_t value)
{
	send(value, HIGH);
}

void lcd_home()
{
        command(LCD_RETURN_HOME);
        _delay_us(2500);
}

// null-terminated string
void lcd_swrite(const char *str)
{
        while(*str != '\0') {
                lcd_write(*str);
                str++;
        }
}
