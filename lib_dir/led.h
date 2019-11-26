#ifndef LED_H
#define LED_H

#include <avr/io.h>

#define SortieLED 0b00000011
#define Entree 0x00

class Led {
    public:
        /**
         *  Constructeur par default
         *  
         *  Ce constructeur initialise le portB pour que les bits les moins
         *  significatif soit en sortie.
         */
        Led();

        /**
         * 
         * 
         */ 
        void turnRed();
        void turnGreen();
        void turnOff();
};

#endif //DEL_H