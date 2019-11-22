#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "couloir.h"

Couloir::Couloir(uint8_t vitesse, LCM* ecran):
    SuiveurLigne(vitesse),
    _lcd(ecran)
{
    DDRC = 0x00; //DDRC en entree
    _lcd->write("Couloir", 0, true);
};

void Couloir::run(){
    while (suivreLigne());
    while (!((PINC & (1 << MILIEU)) || (PINC & (1 << GAUCHE)) || (PINC & (1 << DROITE))))
    {
        suivreCouloir();
    }
    
    while (suivreLigne());
    tournerGauche();
};

void Couloir::suivreCouloir(){
    _delay_ms(50);
    
    if (PINC & (1<<EXTREME_GAUCHE)) {
        correctionDroite();
    }   
    else if (PINC & (1<<EXTREME_DROITE)){
        correctionGauche();
    }else {
        avancerDroit();
    }
}

void Couloir::correctionDroite()
{
    redressementDroit();
    _delay_ms(250);
}

void Couloir::correctionGauche()
{
    redressementGauche();
    _delay_ms(250);
}

