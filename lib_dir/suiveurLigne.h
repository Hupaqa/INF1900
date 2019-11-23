#ifndef SUIVEUR_LIGNE
#define SUIVEUR_LIGNE

#include <util/delay.h>
#include "display.h"

#define MILIEU PINC4
#define GAUCHE PINC3
#define EXTREME_GAUCHE PINC2
#define DROITE PINC5
#define EXTREME_DROITE PINC6

enum DIRECTION{
    AVANT = 0,
    ARRIERE = 1
};

class SuiveurLigne
{
    public:
        SuiveurLigne(uint8_t vitesse);

        void ajustementPWM (uint8_t puissanceDroit, DIRECTION directionDroit, uint8_t puissanceGauche, DIRECTION directionGauche);
        void stopPWM();

        void avancerDroit();
        void redressementDroit();
        void redressementGauche();
        void tournerDroit();
        void tournerGauche();
        void virageGaucheCaree();

        bool suivreLigne();
        bool suiveurLigneAllume();
    protected:
        uint8_t _vitesse;
        static const uint8_t HAUTE_INTENSITE = 90;
        static const uint8_t BASSE_INTENSITE = 32;
        static const uint8_t OFF = 0;
};

#endif