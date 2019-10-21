#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include "led.h"

Led::Led(Port port, uint8_t pin0, uint8_t pin1) :
    port(port),
    pin0(pin0),
    pin1(pin1)
{
}

void Led::turnRed()
{
    switch(port)
    {
    case PORT_A:
        PORTA |= pin0;
        PORTA &= ~pin1;
        break;
    case PORT_B:
        PORTB |= pin0;
        PORTB &= ~pin1;
        break;
    case PORT_C:
        PORTC |= pin0;
        PORTC &= ~pin1;
        break;
    case PORT_D:
        PORTD |= pin0;
        PORTD &= ~pin1;
        break;
    }
}

void Led::turnGreen()
{
    switch(port)
    {
    case PORT_A:
        PORTA |= pin1;
        PORTA &= ~pin0;
        break;
    case PORT_B:
        PORTB |= pin1;
        PORTB &= ~pin0;
        break;
    case PORT_C:
        PORTC |= pin1;
        PORTC &= ~pin0;
        break;
    case PORT_D:
        PORTD |= pin1;
        PORTD &= ~pin0;
        break;
    }
}

void Led::turnOff()
{
    switch(port)
    {
    case PORT_A:
        PORTA &= ~(pin0 | pin1);
        break;
    case PORT_B:
        PORTB &= ~(pin0 | pin1);
        break;
    case PORT_C:
        PORTC &= ~(pin0 | pin1);
        break;
    case PORT_D:
        PORTD &= ~(pin0 | pin1);
        break;
    }
}

void Led::turnAmber(uint16_t ms)
{
    const double VERY_SHORT_DELAY = 1;
    const double SHORT_DELAY = 3;
    uint16_t n = ms >> 2; // divise par 4

    for (uint16_t i = 0; i < n; i++)
    {
    turnRed();
    _delay_ms(VERY_SHORT_DELAY);
    turnGreen();
    _delay_ms(SHORT_DELAY);
    }
}