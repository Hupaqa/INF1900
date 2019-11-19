#ifndef PATH_CORRECTOR
#define PATH_CORRECTOR

#include <avr/io.h>
#include "navigator.h"

#define MILIEU PINC4
#define GAUCHE PINC5
#define EXTREME_GAUCHE PINC6
#define DROITE PINC3
#define EXTREME_DROITE PINC2

class PathCorrector 
{
public:
    PathCorrector(uint8_t vitesse);

    virtual void redressementDroit() = 0;
    virtual void redressementGauche() = 0;

    void initPWM();
    void ajustementPWM (uint8_t puissanceDroit, bool directionDroit, uint8_t puissanceGauche, bool directionGauche);
    void stopPWM();
    
    uint8_t getVitesse();

protected:
    uint8_t _vitesse;
    Navigator _navigator;
};

#endif