#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "couloir.h"

Couloir::Couloir(uint8_t vitesse):
    SuiveurLigne(vitesse)
{
    initPWM();
    DDRC = 0x00; //DDRC en entree
};

void Couloir::run(){
    while (suivreLigne());

    while (!(PINC & ((1<<GAUCHE) | (1<<MILIEU) | (1<<DROITE))))
    {
        suivreCouloir();
    }
    
    while (suivreLigne());
    tournerGauche();
};

void Couloir::suivreCouloir(){
    _delay_ms(50);
    
    if (PINC & (1<<EXTREME_GAUCHE)) {
        redressementDroit();
    }   
    else if (PINC & (1<<EXTREME_DROITE)){
        redressementGauche();
    }else {
        ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
    }
}