#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include "navigator.h"

void ajustementPWM (uint8_t puissanceDroit, uint8_t puissanceGauche)
{
    TCNT1 = 0;

    OCR1A = puissanceDroit;
    OCR1B = puissanceGauche;
    
    TCCR1A = (1<<COM1A1) | (1<<WGM10) | (1<<COM1B1);
    TCCR1B = (1<<CS11);
    TCCR1C = 0;
}