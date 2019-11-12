
#include "suiveurLigne.h"
#include "delay.h"

using namespace suiveurLigne;

void suiveurLigne::redressementDroit(){
    ajustementPWM(32, 0, 96, 0);
    delay_ms (50);
    ajustementPWM(96, 0, 96, 0);
}

void suiveurLigne::redressementGauche(){
    ajustementPWM(96, 0, 32, 0);
    delay_ms (50);
    ajustementPWM(96, 0, 96, 0);
}

void suiveurLigne::tournerDroit(){
    ajustementPWM(0, 0, 128, 0);
    delay_ms (500);
    ajustementPWM(128, 0, 128, 0);
}

void suiveurLigne::tournerGauche(){
    ajustementPWM(128, 0, 0, 0);
    delay_ms (500);
    ajustementPWM(128, 0, 128, 0);
}