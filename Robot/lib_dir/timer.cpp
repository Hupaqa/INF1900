#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "timer.h"

void init_timer1(uint16_t duree_ms)
{
    //avec un prescaler de 64, on fait 125 cycles par ms
    const uint8_t CYCLES_PAR_MS = 125; 
    delayTimer1_cycles = CYCLES_PAR_MS*duree_ms;
    timer1done = false;

    TCNT1 = 0;
    TCCR1A |= (1<<COM1A0)|(1<<COM1A1);
    TCCR1B |= (1<<CS10) | (1<<CS11)| (1<<WGM12) ;
    TCCR1C = 0;
    TIMSK1 |= (1<<OCIE1A);

    delay_timer1();
}

void delay_timer1()
{
    const uint16_t MAX = 0xffff;

    if(delayTimer1_cycles >= MAX)
    {
        OCR1A = 0xffff;
        delayTimer1_cycles -= MAX;
    }
    else
    {
        OCR1A = delayTimer1_cycles;
        delayTimer1_cycles = 0;
    }
    TCNT1 = 0;
} 

void reset_timer1()
{
    TCNT1 = 0;
    OCR1A = 0;
    OCR1B = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1C = 0;
}
