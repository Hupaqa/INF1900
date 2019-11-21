#ifndef BOUCLE_H
#define BOUCLE_H

#include "suiveurLigne.h"

enum class ETAT_BOUCLE {
    ALLER_GROSSE_BOUCLE,
    FAIRE_BOUCLE,
    FIN_BOUCLE,
    QUIT
};

class Boucle {
public:
    Boucle(uint8_t vitesse, LCM* lcd);

    void run();
    void doAction();
    void changeState();

private:
    SuiveurLigne _suiveurLigne;
    ETAT_BOUCLE _etat = ETAT_BOUCLE::ALLER_GROSSE_BOUCLE;
    LCM* _lcd;
};

#endif //BOUCLE_H
