
#include "suiveurLigne.h"
#include "delay.h"

using namespace suiveurLigne;

void suiveurLigne::redressementDroit(){
    ajustementPWM(64, 0, 255, 0);
    delay_ms (100);
    ajustementPWM(128, 0, 128, 0);
}

void suiveurLigne::redressementGauche(){
    ajustementPWM(255, 0, 64, 0);
    delay_ms (100);
    ajustementPWM(128, 0, 128, 0);
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