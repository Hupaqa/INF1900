#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "led.h"

Led::Led(){
    DDRB |= SortieLED;
}

void Led::turnRed()
{
    PORTB |= (1 << PORTB0);
    PORTB &= ~(1 << PORTB1);
}

void Led::turnGreen()
{
    PORTB |= (1 << PORTB1);
    PORTB &= ~(1 << PORTB0); 
}

void Led::turnOff()
{
    PORTB &= ~((1 << PORTB1) | (1 << PORTB0));
}