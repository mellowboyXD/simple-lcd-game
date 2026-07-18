#ifndef LCD_PLAYER_H
#define LCD_PLAYER_H

#include "stdint.h"

struct Vector2 {
    uint8_t x;
    uint8_t y;
};

class Player {
private:
    static const char symbol = 0x7E; /* Big Endian */
public:
};

#endif /* LCD_PLAYER_H */
