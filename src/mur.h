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
    virage
};

class Mur : public SuiveurLigne
{
public:
    Mur(uint8_t vitesse);
    void run();
    void suivreMur();

private:
    Sonar _sonar;
    EtatMur _etat;
};



#endif // MUR_H