#include <LiquidCrystal.h>

#include "screen.hpp"

static constexpr uint8_t RS = 4;
static constexpr uint8_t E  = 6;
static constexpr uint8_t D4 = 11;
static constexpr uint8_t D5 = 10;
static constexpr uint8_t D6 = 9;
static constexpr uint8_t D7 = 8;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 1);
  lcd.write(0x7E);
  lcd.write("hello world");
}

void loop() {
  // put your main code here, to run repeatedly:
}