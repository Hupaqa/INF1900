#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <util/delay.h>

enum Port
{
    PORT_A,
    PORT_B, 
    PORT_C,
    PORT_D
};

void turnRed();

void turnGreen();

void turnOff();

#endif // LED_H