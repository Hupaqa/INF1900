#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <avr/io.h>
#include <util/delay.h>

#define MILIEU PINC4
#define GAUCHE PINC5
#define GGAUCHE PINC6
#define DROITE PINC3
#define DDROITE PINC2

class Navigator {
    public : 
        Navigator(){};

        void initPWM();
        void ajustementPWM (uint8_t puissanceDroit, bool directionDroit, uint8_t puissanceGauche, bool directionGauche);
        void stopPWM();
};
#endif // NAVIGATOR_H