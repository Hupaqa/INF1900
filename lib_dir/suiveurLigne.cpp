#include "suiveurLigne.h"

void SuiveurLigne::redressementDroit(){
    _navigator.ajustementPWM(32, 0, 96, 0);
    while(!(PINC & (1 << MILIEU)));
    _navigator.ajustementPWM(_vitesse, 0, _vitesse, 0);
}

void SuiveurLigne::redressementGauche(){    
    _navigator.ajustementPWM(96, 0, 32, 0);
    while(!(PINC & (1 << MILIEU)));
    _navigator.ajustementPWM(_vitesse, 0, _vitesse, 0);
}

void SuiveurLigne::tournerDroit(){
    _navigator.ajustementPWM(_vitesse, 1, _vitesse, 0);
    while(!(PINC & (1 << DDROITE)));
    _navigator.ajustementPWM(_vitesse, 0, _vitesse, 0);
}

void SuiveurLigne::tournerGauche(){
    _navigator.ajustementPWM(_vitesse, 0, _vitesse, 1);
    while(!(PINC & (1 << GGAUCHE)));
    _navigator.ajustementPWM(_vitesse, 0, _vitesse, 0);
}
