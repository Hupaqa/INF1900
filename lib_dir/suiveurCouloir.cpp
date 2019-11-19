#include "suiveurCouloir.h"

void SuiveurCouloir::redressementDroit(){
    _navigator.ajustementPWM(32, 0, 96, 0);
    _delay_ms(50);
    _navigator.ajustementPWM(_vitesse, 0, _vitesse, 0);
}

void SuiveurCouloir::redressementGauche(){
    Navigator navigator();

    _navigator.ajustementPWM(96, 0, 32, 0);
    _delay_ms(50);
    _navigator.ajustementPWM(_vitesse, 0, _vitesse, 0);
}

void SuiveurCouloir::suivreCouloir(){
    if (PINC & (1<<EXTREME_GAUCHE)) {
        redressementDroit();
    }   
    else if (PINC & 0b00000100){
        redressementGauche();
    }
}