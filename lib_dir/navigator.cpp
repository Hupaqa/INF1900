#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include "navigator.h"

void initPWM()
{
    TCNT1 = 0;
    TCCR1A = (1<<COM1A1) | (1<<WGM10) | (1<<COM1B1);
    TCCR1B = (1<<CS11);
    TCCR1C = 0;
}

void ajustementPWM (uint8_t puissanceDroit, bool directionDroit, uint8_t puissanceGauche, bool directionGauche)
{

    OCR1A = puissanceDroit;
    OCR1B = puissanceGauche;

    if (directionDroit)
    {   
        PORTD |= 0b10000000;
    }else
    {
        PORTD &= 0b01111111;
    }
    

    if (directionGauche)
    {
        PORTD |= 0b01000000;
    }else
    {
        PORTD &= 0b10111111;
    }
}

void turndroite(){
    ajustementPWM(255,1,255,0);
    _delay_ms(10);
    ajustementPWM(124,1,124,0);  //determiner puissance necessaire deux moteurs ?
    _delay_ms(1020); //determiner pour tourner 90 deg droite
    stopPWM();
}

void turngauche(){
    ajustementPWM(255,0,255,1);
    _delay_ms(10);
    ajustementPWM(124,0,124,1); //determiner puissance necessaire deux moteurs ?
    _delay_ms(1000); // determiner pour tourner 90 deg gauche
    stopPWM();
}


void stopPWM(){
    OCR1A = 0;
    OCR1B = 0;
}