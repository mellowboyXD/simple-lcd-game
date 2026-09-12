#ifndef LCD_H
#define LCD_H

#include "utils.h"
#include <stdint.h>

#define LCD_CLEAR               0b00000001 // Clear display
#define LCD_RETURN_HOME         0b00000010

#define LCD_ENTRY_SET           0b00000100
#define LCD_ENTRY_LEFT          0b00000010
#define LCD_ENTRY_RIGHT         0b00000000
#define LCD_ENTRY_INCREMENT     0b00000001
#define LCD_ENTRY_DECREMENT     0b00000000

#define LCD_DISPLAY_CONTROL_SET 0b00001000
#define LCD_DISPLAY_ON          0b00000100 // Display on
#define LCD_DISPLAY_OFF         0b00000000 // Display off

#define LCD_CURSOR_ON           0b00000010
#define LCD_CURSOR_OFF          0b00000000

#define LCD_BLINK_ON            0b00000001
#define LCD_BLINK_OFF           0b00000000

#define LCD_FUNCTION_SET        0b00100000
#define LCD_8BIT_MODE           0b00010000
#define LCD_4BIT_MODE           0b00000000
#define LCD_1_LINE_MODE         0b00000000
#define LCD_2_LINES_MODE        0b00010000
#define LCD_5x8_DOTS            0b00000000
#define LCD_5x10_DOTS           0b00000100

void lcd_init(bool_t four_bit_mode, uint8_t lines, uint8_t rs, uint8_t rw,
	      uint8_t e, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
	      uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

void lcd_clear();

void lcd_display();
void lcd_no_display();

void lcd_cursor();
void lcd_no_cursor();

void lcd_cursor_blink();
void lcd_no_cursor_blink();

void lcd_write(uint8_t value);
void lcd_swrite(const char *str);

void lcd_home();

#endif // LCD_H
