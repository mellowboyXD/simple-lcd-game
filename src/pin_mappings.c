#include "pin_mappings.h"
#include "utils.h"

#include <assert.h>
#include <stdint.h>

// Refer to the arduino datasheet
static uint8_t pinToPortMap[] = {
        PD0,    /* D0 / RX */
        PD1,    /* D1 / TX */
        PD2,    /* D2 */
        PD3,    /* D3 */
        PD4,    /* D4 */
        PD5,    /* D5 */
        PD6,    /* D6 */
        PD7,    /* D7 */

        PB0,    /* D8 */
        PB1,    /* ~D9 */
        PB2,    /* ~D10 */
        PB3,    /* ~D11 */
        PB4,    /* D12 */
        PB5,    /* D13 / LED_BUILTIN */

        PC0,    /* A0 / D14 */
        PC1,    /* A1 / D15 */
        PC2,    /* A2 / D16 */
        PC3,    /* A3 / D17 */
        PC4,    /* A4 / D18 / SDA */
        PC5,    /* A5 / D19 / SCL */
        PC6     /* RESET */
};

uint8_t pport(uint8_t pin)
{
        ASSERT_VALID_PIN;
        return pinToPortMap[pin];
}

void assert_valid_pin(uint8_t pin)
{
        uint8_t size = ARRAY_SIZE(pinToPortMap);
        assert(pin < size && "Invalid port");
}

uint8_t ddrx(uint8_t pin)
{
        ASSERT_VALID_PIN;

        switch(pin) {
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13: /* bank B */
                        return DDRB;
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20: /* bank C */
                        return DDRC;
                default:
                        return DDRD;
        }
}
