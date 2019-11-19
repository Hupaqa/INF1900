#ifndef MUR_H
#define MUR_H

#include "suiveurLigne.h"
#include "sonar.h"
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

    void suivreMur();

private:
    Sonar _sonar;
    EtatMur _etat;
};

#endif // MUR_H