#ifndef MUR_H
#define MUR_H

#include <util/delay.h>
#include <avr/interrupt.h>
#include "suiveurLigne.h"
#include "led.h"

enum EtatMur
{
    debutLigne, 
    suivreMur,
    virageDroit,
    finLigne, 
    virageGauche
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
    void followWall();
    void repositionnerSurLigne();

private:
    EtatMur _etat;
    Led _led;
    LCM* _lcd;
    bool _isDone;
};

#endif // MUR_H