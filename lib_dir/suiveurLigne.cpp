#include "suiveurLigne.h"

void SuiveurLigne::redressementDroit(){
    _navigator.ajustementPWM(32, 0, 96, 0);
    while(!(PINC & (1 << MILIEU)));
    _navigator.ajustementPWM(_vitesse, 0, _vitesse, 0);
};

void SuiveurLigne::redressementGauche(){    
    _navigator.ajustementPWM(96, 0, 32, 0);
    while(!(PINC & (1 << MILIEU)));
    _navigator.ajustementPWM(_vitesse, 0, _vitesse, 0);
};

void SuiveurLigne::tournerDroit(){
    _navigator.ajustementPWM(_vitesse, 1, _vitesse, 0);
    while(!(PINC & (1 << DDROITE)));
    _navigator.ajustementPWM(_vitesse, 0, _vitesse, 0);
};

void SuiveurLigne::tournerGauche(){
    _navigator.ajustementPWM(_vitesse, 0, _vitesse, 1);
    while(!(PINC & (1 << GGAUCHE)));
    _navigator.ajustementPWM(_vitesse, 0, _vitesse, 0);
};

bool SuiveurLigne::suivreLigne(){
    _delay_ms(50);    

    if (!SuiveurLigneAllume())
    {
        _delay_ms(30); //Delais de debounce
        if (!SuiveurLigneAllume())
        {
            _navigator.stopPWM();
            return false;
        }
    }
    else if (!(PINC & (1 << MILIEU)))
    {
        if(PINC & ((1 << EXTREME_GAUCHE) | (1 << GAUCHE)))
        {
            redressementDroit();
        }
        else if (PINC & ((1 << EXTREME_DROITE) | (1 << DROITE))) 
        {
            redressementGauche();
        }
        return true;
    }
    else
    {
        _navigator.ajustementPWM(_vitesse, 0, _vitesse, 0);
        return true;
    }
};

bool SuiveurLigne::suiveurLigneAllume(){
    return PINC & (1<< EXTREME_GAUCHE) ||
           PINC & (1<< GAUCHE) ||
           PINC & (1<< MILIEU) ||
           PINC & (1<< DROITE) ||
           PINC & (1<< EXTREME_DROITE;
};
