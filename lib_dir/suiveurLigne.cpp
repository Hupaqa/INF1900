
#include "suiveurLigne.h"
#include "delay.h"

using namespace suiveurLigne;

void suiveurLigne::redressementDroit(uint8_t vitesse){
    ajustementPWM(vitesse/3, 0, vitesse, 0);
    delay_ms (50);
    ajustementPWM(vitesse, 0, vitesse, 0);
}

void suiveurLigne::redressementGauche(uint8_t vitesse){
    ajustementPWM(vitesse, 0, vitesse/3, 0);
    delay_ms (50);
    ajustementPWM(vitesse, 0, vitesse, 0);
}

void suiveurLigne::tournerDroit(uint8_t vitesse){
    ajustementPWM(0, 0, vitesse, 0);
    while(!(PINC & 0b01110000));
    ajustementPWM(vitesse, 0, vitesse, 0);
}

void suiveurLigne::tournerGauche(uint8_t vitesse){
    ajustementPWM(vitesse, 0, 0, 0);
    while(!(PINC & 0b00011100));
    ajustementPWM(vitesse, 0, vitesse, 0);
}