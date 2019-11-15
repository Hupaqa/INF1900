#ifndef SUIVEUR_COULOIR
#define SUIVEUR_COULOIR

#include "pathCorrector.h"

class SuiveurCouloir : public PathCorrector {
    public:
        SuiveurCouloir(uint8_t vitesse): PathCorrector(vitesse) {};

        void redressementDroit();
        void redressementGauche();
};

#endif