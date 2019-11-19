#define F_CPU 8000000UL

#include <avr/io.h>
#include "led.h"
#include "uart.h"
#include "delay.h"
#include "navigator.h"
#include "timer.h"

volatile uint32_t delayTimer1_cycles;
volatile bool timer1done;

ISR (TIMER1_COMPA_vect)
{
    if(delayTimer1_cycles == 0){
        reset_timer1();
        timer1done = true;
    }
    else {
        delay_timer1();
    }
}

int main() 
{
    Led led(PORT_C, 0, 1);
    led.turnGreen();
    initialisationUART();
    delay_cycles(0x80);
    ajustementPWM(10, 90);
    init_timer1(10000);
    reset_timer1();
    return 0;
}