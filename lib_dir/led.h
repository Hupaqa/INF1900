#ifndef LED_H
#define LED_H

#include <avr/io.h>

#define SortieLED 0b00000011
#define Entree 0x00

class Led {
    public:
        Led();

        void turnRed();
        void turnGreen();
        void turnOff();
};

#endif //DEL_H