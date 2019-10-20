#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include "utils.h"

void delay_cycles(uint16_t cycles)
{
    const uint16_t MAXCYCLES = 65535; //Propre a la fonction _delay_loop_2
    cycles /= 4; //Propre a la fonction _delay_loop_2

    while(cycles > 0){
       if (cycles > MAXCYCLES){
            _delay_loop_2 (0); 
            cycles-=MAXCYCLES;
        }
        else{
            _delay_loop_2(cycles);
            cycles=0;
        } 
    }
}

void ajustementPWM (uint8_t puissanceDroit, uint8_t puissanceGauche)
{
    TCNT1 = 0;

    OCR1A = puissanceDroit;
    OCR1B = puissanceGauche;
    
    TCCR1A = ((1<<COM1A1)|(1<<WGM10)|(1<<COM1B1));
    TCCR1B = (1<<CS11);
    TCCR1C = 0;
}