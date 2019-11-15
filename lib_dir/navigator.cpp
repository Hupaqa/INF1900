#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include "navigator.h"

void Navigator::initPWM()
{
    TCNT1 = 0;
    TCCR1A = (1<<COM1A1) | (1<<WGM10) | (1<<COM1B1);
    TCCR1B = (1<<CS11);
    TCCR1C = 0;
}

void Navigator::ajustementPWM (uint8_t puissanceDroit, bool directionDroit, uint8_t puissanceGauche, bool directionGauche)
{
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

    //Vitesse maximal pour surpasser l'inertie
    OCR1A = (puissanceDroit) ? UINT8_MAX : 0;
    OCR1B = (puissanceGauche) ? UINT8_MAX : 0;

    _delay_ms(5); //temps determine experimentalement

    OCR1A = puissanceDroit;
    OCR1B = puissanceGauche;
}

void Navigator::stopPWM(){
    OCR1A = 0;
    OCR1B = 0;
}