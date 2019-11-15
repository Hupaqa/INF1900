#ifndef F_CPU 
#define F_CPU 8000000UL
#endif

#define MILIEU PINC4
#define GAUCHE PINC5
#define GGAUCHE PINC6
#define DROITE PINC3
#define DDROITE PINC2

#include "suiveurLigne.h"
#include "delay.h"

using namespace suiveurLigne;

void suiveurLigne::redressementDroit(uint8_t vitesse)
{
    ajustementPWM(0, 0, 255, 0);
    _delay_ms(5);
    ajustementPWM(32, 0, 96, 0);
    while(!(PINC & (1 << MILIEU)));
    ajustementPWM(vitesse, 0, vitesse, 0);
}

void suiveurLigne::redressementGauche(uint8_t vitesse){
    ajustementPWM(255, 0, 0, 0);
    _delay_ms(5);
    ajustementPWM(92, 0, 32, 0);
    while(!(PINC & (1 << MILIEU)));
    ajustementPWM(vitesse, 0, vitesse, 0);
}

void suiveurLigne::tournerDroit(uint8_t vitesse){
    ajustementPWM(255, 1, 255, 0);
    _delay_ms(5);
    ajustementPWM(vitesse, 1, vitesse, 0);
    while(!(PINC & (1 << DDROITE)));
    ajustementPWM(vitesse, 0, vitesse, 0);
}

void suiveurLigne::tournerGauche(uint8_t vitesse){
    ajustementPWM(255, 0, 255, 1);
    _delay_ms(5);
    ajustementPWM(vitesse, 0, vitesse, 1);
    while(!(PINC & (1 << GGAUCHE)));
    ajustementPWM(vitesse, 0, vitesse, 0);
}