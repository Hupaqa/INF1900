#define F_CPU 8000000UL

#include <avr/io.h>
#include "led.h"
#include "uart.h"
#include "delay.h"
#include "navigator.h"

int main() 
{
    Led led(PORT_C, 0, 1);
    led.turnGreen();
    initialisationUART();
    delay_cycles(0x80);
    ajustementPWM(10, 90);
    return 0;
}