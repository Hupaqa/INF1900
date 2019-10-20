#define F_CPU 8000000UL

#include <avr/io.h>
#include "led.h"
#include "uart.h"
#include "utils.h"

int main() 
{
    turnLedAmber(1, PORTB, PORTB0, PORTB1);
    turnLedGreen(PORTB, PORTB0, PORTB1);
    initialisationUART();
    delay_cycles(0x80);
    ajustementPWM(10, 90);
    return 0;
}