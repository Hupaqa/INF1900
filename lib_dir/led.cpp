#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include "led.h"

LED::Led(){
    DDRB |= SortieDel;
}

void turnRed()
{
    PORTB |= (1 << PORTB0);
    PORTB &= ~(1 << PORTB1);
}

void turnGreen()
{
    PORTB |= (1 << PORTB1);
    PORTB &= ~(1 << PORTB0); 
}

void turnOff()
{
    PORTB &= ~((1 << PORTB1) | (1 << PORTB0));
}