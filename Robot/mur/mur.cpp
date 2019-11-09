#define F_CPU 8000000UL

#include "mur.h"
#include "uart.h"

void init()
{
    // Compteur
    TCCR2B |= (1 << CS22); // Prescaler de 64

    // Interruption
    EICRA |= (1 << ISC20); // Any edge
}

void fetch()
{
    PORTB |= (1 << PORTB4);
    _delay_us(10);
    PORTB &= ~(1 << PORTB4);

    listening = true;

    EIMSK |= (1 << INT2); // Active les interruptions sur INT2
    sei(); // Active les interruptions
}

ISR(INT2_vect)
{
    if (listening)
    {
        TCNT2 = 0; // Reinitialise la valeur du compteur
        TIMSK2 |= (1 << TOIE2); // Interrupt on overflow
        listening = false;

    }
    else 
    {   
        cli(); // Stop interrupts
        TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
        distance = (TCNT2 * 8) / 58;
        repondu = true;
    }
}

ISR(TIMER2_OVF_vect)
{
    cli();
    TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
    distance = 35;
    repondu = true;
}

int main()
{
    DDRB |= (1 << PORTB4); 
    DDRB &= ~(1 << PORTB2);
    initialisationUART();


    init();
    while(true)
    {
        fetch();
        while(!repondu);
        transmissionUART(distance);
        _delay_ms(500);
    }
}