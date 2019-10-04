#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "can.h"

void initialisationUART() 
{
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications
    UBRR0H = 0;
    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

// De l'USART vers le PC
void transmissionUART(uint8_t donnee) 
{
    while ( !( UCSR0A & (1<<UDRE0)) )
    {
    }
    UDR0 = donnee;
}

/*
 * Affecte la valeur correspondante à la couleur rouge aux pins 0 et 1 du port B.
*/
void turnLedRed()
{
    PORTB = (PORTB | (1 << PORTB1)) & ~(1 << PORTB0); // set to xxxxxx10
}

/*
 * Affecte la valeur correspondante à la couleur verte aux pins 0 et 1 du port B.
*/
void turnLedGreen()
{
    PORTB = (PORTB | (1 << PORTB0)) & ~(1 << PORTB1); // set to xxxxxx01
}

/*
 * Affecte aucune tension sur les pins 0 et 1 pour fermer la LED.
*/
void turnLedOff()
{
    PORTB &= ~((1 << PORTB1) | (1 << PORTB0)); // set to xxxxxx00
}

/*
 * Affecte en alternance les couleurs rouges et vertes pour obtenir la couleur
 * ambre. 
*/
void turnLedAmber()
{
    const double VERY_SHORT_DELAY = 1;
    const double SHORT_DELAY = 3;

    turnLedRed();
    _delay_ms(VERY_SHORT_DELAY);
    turnLedGreen();
    _delay_ms(SHORT_DELAY); // Add a little more green to achieve amber
}

int main()
{
    DDRB = 0xff;
    DDRA = 0x00;
    initialisationUART();
    can convertisseur = can();
    uint8_t position = 0x00;

    turnLedGreen();

    while(true)
    {
        uint8_t lecture = convertisseur.lecture(position) & 0xFF;
        if (lecture < 0x70)
        {
            turnLedGreen();
            _delay_ms(1000);
        }
        else if (lecture >= 0x70 && lecture <= 0x80)
        {
            for (uint8_t i = 0; i < 0xfa; i++)
            {
                turnLedAmber();
            }
        }
        else
        {
            turnLedRed();
            _delay_ms(1000);
        }
    }   
}