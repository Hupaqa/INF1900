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
    ajustementPWM(OFF, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
};

void SuiveurLigne::redressementGauche()
{  
    ajustementPWM(_vitesse, DIRECTION::AVANT, OFF, DIRECTION::AVANT);
};

void SuiveurLigne::tournerDroit()
{
    ajustementPWM(_vitesse, DIRECTION::ARRIERE, _vitesse, DIRECTION::AVANT);
    while(!(PINC & (1 << GAUCHE))); // Attend de toucher la ligne(test William pour Sonar)
    // ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT); necessaire ?
};

void SuiveurLigne::tournerGauche()
{
    ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::ARRIERE);
    while(!(PINC & (1 << EXTREME_GAUCHE))); // Attend de toucher la ligne
    // ajustementPWM(_vitesse,DIRECTION::AVANT, _vitesse, DIRECTION::AVANT); necessaire ?
};

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
            redressementDroit();
        }
        else if (PINC & (1 << EXTREME_DROITE) || PINC & (1 << DROITE)) 
        {
            redressementGauche();
        }
        return true;
    }
    else
    {
        avancerDroit();
        return true;
    }
    return true; // Masque le warning
};

bool SuiveurLigne::suiveurLigneAllume()
{
    return (PINC & (1<< EXTREME_GAUCHE) ||
            PINC & (1<< GAUCHE) ||
            PINC & (1<< MILIEU) ||
            PINC & (1<< DROITE) ||
            PINC & (1<< EXTREME_DROITE));
};
