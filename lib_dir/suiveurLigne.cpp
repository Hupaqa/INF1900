#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "suiveurLigne.h"
#include "uart.h"

SuiveurLigne::SuiveurLigne(uint8_t vitesse) :
    Navigator(vitesse)
{
};

void SuiveurLigne::avancerDroit()
{
    ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
}

void SuiveurLigne::redressementDroit()
{
    ajustementPWM(BASSE_INTENSITE, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);

};

void SuiveurLigne::redressementGauche()
{ 
    ajustementPWM(_vitesse, DIRECTION::AVANT, BASSE_INTENSITE, DIRECTION::AVANT);
};

void SuiveurLigne::tournerDroit()
{
    ajustementPWM(_vitesse, DIRECTION::ARRIERE, _vitesse, DIRECTION::AVANT);
    while(!(PINC & (1 << EXTREME_DROITE)));
};

void SuiveurLigne::tournerGauche()
{
    ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::ARRIERE);
    while(!(PINC & (1 << EXTREME_GAUCHE)));
};

void SuiveurLigne::virageGaucheCaree()
{
    const uint16_t AVANCER_AVANT_VIRAGE = 1000;

    avancerDroit();
    _delay_ms(AVANCER_AVANT_VIRAGE);
    tournerGauche();
}

bool SuiveurLigne::suivreLigne()
{
    const uint8_t FETCH_DELAY = 75;
    const uint8_t DEBOUNCE_DELAY = 15;

    _delay_ms(FETCH_DELAY);

    if (!suiveurLigneAllume())
    {
        _delay_ms(DEBOUNCE_DELAY);
        if (!suiveurLigneAllume())
        {
            stopPWM();
            return false;
        }
    }
    else if (!(PINC & (1 << MILIEU)))
    {
        if(PINC & (1 << EXTREME_GAUCHE) || PINC & (1 << GAUCHE))
        {
            redressementGauche();
        }
        else if (PINC & (1 << EXTREME_DROITE) || PINC & (1 << DROITE)) 
        {
            redressementDroit();
        }
        return true;
    }
    else
    {
        avancerDroit();
        return true;
    }
};

bool SuiveurLigne::suiveurLigneAllume()
{
    return (PINC & (1<< EXTREME_GAUCHE) ||
            PINC & (1<< GAUCHE) ||
            PINC & (1<< MILIEU) ||
            PINC & (1<< DROITE) ||
            PINC & (1<< EXTREME_DROITE));
};
