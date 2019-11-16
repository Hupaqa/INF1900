#ifndef SUIVEUR_LIGNE
#define SUIVEUR_LIGNE

#include "pathCorrector.h"

class SuiveurLigne : public PathCorrector 
{
    public:
        SuiveurLigne(uint8_t vitesse);

        void redressementDroit();
        void redressementGauche();

        void tournerDroit();
        void tournerGauche();
    
    private:

};

#endif