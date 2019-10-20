#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include "led.h"

void turnLedRed(int port, int pin1, int pin2)
{
    port |= (1 << pin1);
    port &= ~(1 << pin2); // set to xxxxxx10
}

void turnLedGreen(int port, int pin1, int pin2)
{
    port |= (1 << pin1);
    port &= ~(1 << pin2); // set to xxxxxx01
}

void turnLedOff(int port, int pin1, int pin2)
{
    port &= ~((1 << pin2) | (1 << pin1)); // set to xxxxxx00
}

void turnLedAmber(uint16_t ms, int port, int pin1, int pin2)
{
    const double VERY_SHORT_DELAY = 1;
    const double SHORT_DELAY = 3;
    uint16_t nTimes = ms >> 2; // to divize by four

    for (uint16_t i = 0; i < nTimes; i++)
    {
    turnLedRed(port, pin1, pin2);
    _delay_ms(VERY_SHORT_DELAY);
    turnLedGreen(port, pin1, pin2);
    _delay_ms(SHORT_DELAY); // Add a little more green to achieve amber
    }
}