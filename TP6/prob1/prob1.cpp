#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>

enum Etat
{
    INIT,
    INCREMENTATION,
    OUTPUT,
};

volatile bool bontonEnfonce = false;
volatile uint8_t compteur = 0;

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

void transmissionUART(uint8_t donnee) 
{
    while ( !( UCSR0A & (1<<UDRE0)) )
    {
    }
    UDR0 = donnee;
}

ISR (INT0_vect)
{
    _delay_ms(30);
    if (PIND & 0x04)
    {
        bontonEnfonce = false;
    }
    else
    {
        bontonEnfonce = true;
    }
    EIFR |= (1 << INTF0);
}

ISR (TIMER1_COMPA_vect)
{
    compteur++;
}

void turnLedRed()
{
    PORTB = (PORTB | (1 << PORTB1)) & ~(1 << PORTB0); // set to xxxxxx10
}

/*
 * Affecte la valeur correspondante à la couleur verte aux pins 0 et 1 du port A.
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

void flashRed()
{
    turnLedRed();
    _delay_ms(250);
    turnLedOff();
    _delay_ms(250);
}

void initialisationInit()
{
    EIMSK |= (1 << INT0); // Permet les external interrupts
    EICRA |= (1 << ISC01); // Interrupt on falling edge
    sei(); // Active les interrupts
}

void initialisationIncrementation()
{
    EIMSK |= (1 << INT0); // Permet les external interrupts
    EICRA |= (1 << ISC01) | (1 << ISC00); // Interrupt on rising edge
    TCNT1 = 0; // Initialise le compteur = 0
    OCR1A = 12500; // Permet un interrupt a chaque 100ms
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10); // Prescaler de 64 et CTC
    TIMSK1 |= (1 << OCIE1A); // Active les interrupts
    sei(); // Active les interrupts
}

void doAction(const Etat& etat)
{
    switch(etat)
    {
    case INIT:
        compteur = 0;
        bontonEnfonce = false;
        initialisationInit();
        break;
    case INCREMENTATION:
        initialisationIncrementation();
        break;
    case OUTPUT:
        turnLedGreen();
        _delay_ms(500);
        turnLedOff();
        _delay_ms(2000);
        compteur /= 0b10;
        for (uint8_t i = 0; i < compteur; i++)
        {
            flashRed();
            transmissionUART(i);
        }
        turnLedGreen();
        _delay_ms(1000);
        turnLedOff();
        break;
    }
}

void changeState(Etat& etat)
{
    switch (etat)
    {
    case INIT:
        
        while(!bontonEnfonce);
        cli();
        etat = Etat::INCREMENTATION;
        break;
    case INCREMENTATION:
        while (bontonEnfonce && compteur < 0x78)
        {
        }
        cli();
        etat = Etat::OUTPUT;
        break;
    case OUTPUT:
        etat = Etat::INIT;
        break;
    }
}

int main()
{
    DDRD = 0x00;
    DDRB = 0xff;
    initialisationUART();
    Etat etat = Etat::INIT;
    while (true)
    {
        doAction(etat);
        changeState(etat);
    }
}