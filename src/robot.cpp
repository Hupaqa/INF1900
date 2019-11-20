/*
Pour le suiveur de ligne
U1 = PC3
U2 = PC4
U3 = PC5
U4 = PC6
U5 = PC7

*/

#define F_CPU 8000000UL
#define ddr_lcd DDRA
#define port_lcd PORTA

#include "suiveurLigne.h"
#include "uart.h"

uint8_t VITESSE = 100;

int main()
{
    DDRB |= (1 << PORTB4); 
    DDRB &= ~(1 << PORTB2);
    DDRC = 0x00;
    DDRD = 0xff;
    initialisationUART();

    SuiveurLigne suivre = SuiveurLigne(70);
    suivre.initPWM();
    while(suivre.suivreLigne());
    /*
    SuiveurLigne suivre = SuiveurLigne(75);
    suivre.initPWM();

    while(suivre.suivreLigne());
    return 0;
    */
}


