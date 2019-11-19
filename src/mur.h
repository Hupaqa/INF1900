#ifndef MUR_H
#define MUR_H

#include <avr/delay.h>
#include <avr/interrupt.h>
#include "suiveurLigne.h"
#include "led.h"

enum EtatMur
{
    debutLigne, 
    mur,
    finLigne, 
    virage,
    fin
};

class Mur : public SuiveurLigne
{
public:
    Mur(uint8_t vitesse);

    void run();
    void doAction();
    void changeState();

    void fetchSonar();

    void moveToWall();
    void moveAgainstWall();
    void goStraight();
    void followWall();

private:
    const uint8_t DEMARAGE = 254;
    const uint8_t HAUTE_INTENSITE = 95;
    const uint8_t BASSE_INTENSITE = 38;
    const uint8_t AVANT = 0;
    const uint8_t ARRIERE = 1;
    const uint8_t OFF = 0;
    EtatMur _etat;
};

#endif // MUR_H