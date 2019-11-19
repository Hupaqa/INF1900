#ifndef COULOIR_H
#define COULOIR_H

#include "suiveurLigne.h"
#include "suiveurCouloir.h"

class Couloir {
    public:
        Couloir(uint8_t vitesse);
        void run();

    private:
        SuiveurLigne _suiveurLigne;
        SuiveurCouloir _suiveurCouloir;
};

#endif