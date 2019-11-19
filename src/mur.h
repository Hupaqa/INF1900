#ifndef MUR_H
#define MUR_H

#include "suiveurLigne.h"
#include "sonar.h"

enum EtatMur
{
    debutLigne, 
    mur,
    finLigne, 
    virage
};

class Mur
{
public:
    Mur(uint8_t vitesse);
    void run();
    void suivreMur();
    void suivreLigne();
    void virageGauche();

private:
    SuiveurLigne _suiveurLigne;
    Sonar _sonar;
    Etat _etat;
};



#endif // MUR_H