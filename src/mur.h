#ifndef MUR_H
#define MUR_H

#include <util/delay.h>
#include <avr/interrupt.h>
#include "suiveurLigne.h"
#include "led.h"

enum class EtatMur
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
    Mur(uint8_t vitesse, LCM* lcd);
    ~Mur();

    void run();
    void doAction();
    void changeState();

    void enableSonar();
    void fetchSonar();

    void moveToWall();
    void moveAgainstWall();
    void goStraight();
    void followWall();

private:
    // const uint8_t DEMARAGE = 254;
    // const uint8_t HAUTE_INTENSITE = 105;
    // const uint8_t BASSE_INTENSITE = 38;
    // const uint8_t AVANT = 0;
    // const uint8_t ARRIERE = 1;
    bool stayCurrentState;
    EtatMur _etat;
    Led _led;
    LCM* _lcd;
};

#endif // MUR_H