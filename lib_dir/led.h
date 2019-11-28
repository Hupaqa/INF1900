#ifndef LED_H
#define LED_H

#include <avr/io.h>

class Led {
public:
    /*
     *  Constructeur par défaut
     * 
     *  Initialise le data direction register pour que PINB0 (+) et PINB1 (-) 
     *  soient en sortie pour la LED.
     */
    Led();

    /*
     *  turnRed
     * 
     *  Configure PINB0 (+) et PINB1 (-) pour que la LED soit rouge.
     */
    void turnRed();

    /*
     *  turnRed
     * 
     *  Configure PINB0 (+) et PINB1 (-) pour que la LED soit verte.
     */
    void turnGreen();

    /*
     *  turnRed
     * 
     *  Configure PINB0 (+) et PINB1 (-) pour que la LED soit éteinte.
     */
    void turnOff();
};

#endif //DEL_H