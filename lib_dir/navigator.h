#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <avr/io.h>
#include <util/delay.h>

#define MILIEU PINC4
#define GAUCHE PINC5
#define GGAUCHE PINC6
#define DROITE PINC3
#define DDROITE PINC2

class Navigator {
    public : 
        Navigator(){};

        void initPWM();
        void ajustementPWM (uint8_t puissanceDroit, bool directionDroit, uint8_t puissanceGauche, bool directionGauche);
        void stopPWM();
}

class PathCorrector {
    public:
        PathCorrector(uint8_t vitesse = UINT8_MAX/2) : _vitesse (vitesse){};

        void redressementDroit() = 0;
        void redressementGauche() = 0;

    private:
        uint8_t _vitesse;
}

class SuiveurLigne : PathCorrector {
    public:
        SuiveurLigne(uint8_t vitesse) : PathCorrector(vitesse) {};

        void redressementDroit();
        void redressementGauche();

        void tournerDroit();
        void tournerGauche();
}

class SuiveurCouloir : PathCorrector {
    public:
        SuiveurCouloir(uint8_t vitesse): PathCorrector(vitesse) {};

        void redressementDroit();
        void redressementGauche();

}

#endif // NAVIGATOR_H