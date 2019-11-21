#ifndef SUIVEUR_LIGNE
#define SUIVEUR_LIGNE

#include "navigator.h"
#include "display.h"

#define DDR DDRA
#define PORT PORTA


class SuiveurLigne : public Navigator 
{
    public:
        SuiveurLigne(uint8_t vitesse);

        void avancerDroit();
        void redressementDroit();
        void redressementGauche();

        void tournerDroit();
        void tournerGauche();

        bool suivreLigne();
        bool suiveurLigneAllume();
    private:
        const uint8_t OFF = 0;
};

#endif