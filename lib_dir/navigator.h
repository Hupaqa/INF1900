#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <avr/io.h>
#include <util/delay.h>

#define MILIEU PINC4
#define GAUCHE PINC5
#define EXTREME_GAUCHE PINC6
#define DROITE PINC3
#define EXTREME_DROITE PINC2

enum class DIRECTION{
    AVANT = 0,
    ARRIERE = 1
};

class Navigator {
    public : 
        Navigator(uint8_t vitesse);

        void initPWM();
        void ajustementPWM (uint8_t puissanceDroit, DIRECTION directionDroit, uint8_t puissanceGauche, DIRECTION directionGauche);
        void stopPWM();

        virtual void redressementDroit(){};
        virtual void redressementGauche(){};

        uint8_t getVitesse();

    protected:
        uint8_t _vitesse;
};

#endif // NAVIGATOR_H