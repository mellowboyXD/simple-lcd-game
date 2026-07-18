/**
 * Utility class for lcd display. Provides screen dimensions and others.
 */
#ifndef LCD_SCREEN_H
#define LCD_SCREEN_H

#include "stdint.h"

class Screen {
private:
  static constexpr uint8_t width = 16;
  static constexpr uint8_t height = 2;

public:
  static constexpr uint8_t GetWidth();
  static constexpr uint8_t GetHeight();
};

#endif /* LCD_SCREEN_H */
