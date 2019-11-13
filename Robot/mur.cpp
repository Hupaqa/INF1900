#define F_CPU 8000000UL

#include "mur.h"
#include "uart.h"
#include "suiveurLigne.h"
#include "navigator.h"


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
    repondu = false;

    TCCR2B |= (1 << CS22);
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
        TCCR2B = 0;
        TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
        distance = (TCNT2 * 8) / 58;
        transmissionUART(distance);
        repondu = true;
        sei();
    }
}

ISR(TIMER2_OVF_vect)
{
    cli();
    TCCR2B = 0;
    TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
    distance = 35;
    transmissionUART(distance);
    repondu = true;
    transmissionUART(1);
    sei();
}

void tourner()
{
    const uint8_t BASE = 85;
    const uint8_t DEMARAGE = 254;
    const uint8_t GEARSHIFT = 180;
    const uint8_t DELAY_DEMARAGE = 5;
    const uint8_t AVANT = 0;
    const uint8_t ARRIERE = 1;
    const uint8_t HAUTE_INTENSITE = 118;

    if (distance > 18) // tourne gauche
    {
        ajustementPWM(DEMARAGE, AVANT, 0, AVANT);
        _delay_ms(DELAY_DEMARAGE);
        //ajustementPWM(GEARSHIFT, AVANT, 0, AVANT);
        //_delay_ms(DELAY_DEMARAGE);
        ajustementPWM(HAUTE_INTENSITE, AVANT, 0, AVANT);
    }
    else if (distance < 13 && distance > 1) // tourne droite
    {
        ajustementPWM(0, AVANT, DEMARAGE, AVANT);
        _delay_ms(DELAY_DEMARAGE);
        //ajustementPWM(0, AVANT, GEARSHIFT, AVANT);
        //_delay_ms(DELAY_DEMARAGE);
        ajustementPWM(0, AVANT, HAUTE_INTENSITE, AVANT);
    }
    else
    {
        ajustementPWM(DEMARAGE, AVANT, DEMARAGE, AVANT);
        _delay_ms(DELAY_DEMARAGE);
        //ajustementPWM(GEARSHIFT, AVANT, GEARSHIFT, AVANT);
        //_delay_ms(DELAY_DEMARAGE);
        ajustementPWM(BASE, AVANT, BASE, AVANT);
    }
    _delay_ms(50);
}


int main()
{
    DDRB |= (1 << PORTB4); 
    DDRB &= ~(1 << PORTB2);
    DDRD = 0xff;
    initialisationUART();
    initPWM();

    init();
    while(true)
    {
        fetch();
        while(!repondu);
        tourner();
    } 
}