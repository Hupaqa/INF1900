#ifndef SONAR_H
#define SONAR_H

#include <util/delay.h>
#include <avr/interrupt.h>
#include "pathCorrector.h"

// Variables globales pour les interruptions déclarées dans mur.cpp
extern volatile uint8_t distance;
extern volatile bool repondu;
extern volatile bool listening;

class Sonar : public PathCorrector 
{
public:
    Sonar(uint8_t vitesse);
    ~Sonar();
    
    void fetch();
    void redressementDroit();
    void redressementGauche();
    void avancerDroit();

private:
    const uint8_t DEMARAGE = 254;
    const uint8_t DELAY_DEMARAGE = 5;
    const uint8_t HAUTE_INTENSITE = 118;
    const uint8_t AVANT = 0;
    const uint8_t ARRIERE = 1;
    const uint8_t OFF = 0;
    const uint8_t SONAR_DELAY = 10;
};

#endif