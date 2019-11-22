#ifndef BOUCLE_H
#define BOUCLE_H

#include "suiveurLigne.h"

enum class ETAT_BOUCLE {
    ALLER_GROSSE_BOUCLE,
    FAIRE_BOUCLE,
    FIN_BOUCLE,
    QUIT
};

class Boucle : public SuiveurLigne 
{
public:
    Boucle(uint8_t vitesse, LCM* lcd);

    void run();
    void doAction();
    void changeState();

    bool boucleDetectee();
    void allerGrosseBoucle();
    void suivreBoucles();

private:
    ETAT_BOUCLE _etat;
    LCM* _lcd;

    const uint8_t intersectionGrosseBoucle = 2;
    const uint8_t nBoucles = 2;
    const uint8_t nSegments = 3;
};

#endif //BOUCLE_H
