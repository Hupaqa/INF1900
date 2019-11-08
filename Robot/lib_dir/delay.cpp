#ifndef F_CPU
# define F_CPU 8000000UL
#endif

#include "delay.h"


void delay_ms(uint16_t delais_ms)
{
    uint16_t cycles_par_ms = F_CPU/(4*1000);
    
    while (delais_ms != 0){
        _delay_loop_2(cycles_par_ms);
        delais_ms--;
    }
}
