#ifndef SUIVEUR_LIGNE
#define SUIVEUR_LIGNE

#include "pathCorrector.h"

class SuiveurLigne : public PathCorrector {
    public:
        SuiveurLigne(uint8_t vitesse) : PathCorrector(vitesse) {};

        virtual void redressementDroit();
        virtual void redressementGauche();

        void tournerDroit();
        void tournerGauche();
};

#endif