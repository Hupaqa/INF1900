#define F_CPU 8000000UL

#include <avr/io.h>
#include "memoire_24.h"
#include "uart.h"
#include "led.h"

uint16_t getNombreInstruction()
{
    uint8_t high = receptionUART();
    uint8_t low = receptionUART();
    uint16_t nInstructions = (high << 8) | low;
    return nInstructions - 2;
}

int main() 
{
    DDRB = 0xff;
    Memoire24CXXX mem;
    initialisationUART();
    turnRed();

    uint16_t nInstructions = getNombreInstruction();
    uint8_t lecture;

    for (uint16_t i = 0; i < nInstructions; ++i)
    {
        lecture = receptionUART();
        mem.ecriture(i, lecture);
        _delay_ms(MEM_DELAY);
    }
    turnGreen();
}
