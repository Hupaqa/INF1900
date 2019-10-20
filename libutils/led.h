#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <util/delay.h>

void turnLedRed(int port, int pin1, int pin2);

void turnLedGreen(int port, int pin1, int pin2);

void turnLedOff(int port, int pin1, int pin2);

void turnLedAmber(uint16_t ms, int port, int pin1, int pin2);

#endif // LED_H