#ifndef SUIVEUR_COULOIR
#define SUIVEUR_COULOIR

#include "pathCorrector.h"

class SuiveurCouloir : public PathCorrector {
    public:
        SuiveurCouloir(uint8_t vitesse): PathCorrector(vitesse) {};

        virtual void redressementDroit();
        virtual void redressementGauche();
};

#endif