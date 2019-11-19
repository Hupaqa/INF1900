#ifndef SUIVEUR_LIGNE
#define SUIVEUR_LIGNE

#include "navigator.h"

class SuiveurLigne : public Navigator 
{
    public:
        SuiveurLigne(uint8_t vitesse);

        virtual void redressementDroit();
        virtual void redressementGauche();

        void tournerDroit();
        void tournerGauche();

        virtual bool suivreLigne();
        bool suiveurLigneAllume();
    
    private:

};

#endif