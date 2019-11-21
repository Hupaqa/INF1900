#ifndef F_CPU
# define F_CPU 8000000UL
#endif
#ifndef UINT8_MAX
#define UINT8_MAX 255
#endif

#include "navigator.h"
#include <stdint.h>

Navigator::Navigator(uint8_t vitesse) : 
    _vitesse(vitesse)
{
    initPWM();
};

void Navigator::initPWM()
{
    TCNT1 = 0;
    TCCR1A = (1<<COM1A1) | (1<<WGM10) | (1<<COM1B1);
    TCCR1B = (1<<CS11);
    TCCR1C = 0;
}

void Navigator::ajustementPWM(uint8_t puissanceDroit, DIRECTION directionDroit, uint8_t puissanceGauche, DIRECTION directionGauche)
{
    if (directionDroit == DIRECTION::AVANT)
    {   
        PORTD &= ~(1 << PORTD7);
    }
    else
    {
        PORTD |= (1 << PORTD7);   
    }

    if (directionGauche == DIRECTION::AVANT)
    {
        PORTD &= ~(1 << PORTD6);
    }
    else
    {
        PORTD |= (1 << PORTD6);
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

uint8_t Navigator::getVitesse()
{
    return _vitesse;
};