#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include "delay.h"

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