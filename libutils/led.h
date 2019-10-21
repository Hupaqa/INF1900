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

class Led
{
    public:
    Led(Port port, uint8_t pin0, uint8_t pin1);

    void turnRed();
    void turnGreen();
    void turnOff();
    void turnAmber(uint16_t ms);

    private:
    Port port;
    uint8_t pin0;
    uint8_t pin1;
};

#endif // LED_H