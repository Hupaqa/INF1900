#include "sonar.h"

Sonar::Sonar(uint8_t vitesse) : 
    PathCorrector(vitesse)
{
    // Interruption
    EICRA |= (1 << ISC20); // Any edge
}

Sonar::~Sonar()
{
    TCCR2B = 0; // Disable the counter
}

void Sonar::fetch()
{
    const uint8_t SONAR_DELAY = 10;
    
    cli();
    PORTB |= (1 << PORTB4);
    _delay_us(SONAR_DELAY);
    PORTB &= ~(1 << PORTB4);

    listening = true;
    repondu = false;

    TCCR2B |= (1 << CS22); // Active le compteur, prescaler de 64
    EIMSK |= (1 << INT2); // Active les interruptions sur INT2
    sei(); // Active les interruptions
}

void Sonar::redressementDroit()
{
    const uint8_t DELAY_DEMARAGE = 5;

<<<<<<< HEAD
    _navigator.ajustementPWM(DEMARAGE, AVANT, OFF, AVANT);
=======
    _navigator.ajustementPWM(DEMARAGE, AVANT, DEMARAGE, AVANT);
>>>>>>> dbc510c2f5222582b184ed01fe100d0af9e4802c
    _delay_ms(DELAY_DEMARAGE);
    _navigator.ajustementPWM(_vitesse, AVANT, BASSE_INTENSITE, AVANT);
}

void Sonar::redressementGauche()
{
    const uint8_t DELAY_DEMARAGE = 5;

<<<<<<< HEAD
    _navigator.ajustementPWM(OFF, AVANT, DEMARAGE, AVANT);
=======
    _navigator.ajustementPWM(DEMARAGE, AVANT, DEMARAGE, AVANT);
>>>>>>> dbc510c2f5222582b184ed01fe100d0af9e4802c
    _delay_ms(DELAY_DEMARAGE);
    _navigator.ajustementPWM(BASSE_INTENSITE, AVANT, _vitesse, AVANT);
}

void Sonar::avancerDroit()
{
    const uint8_t DELAY_DEMARAGE = 5;

    _navigator.ajustementPWM(DEMARAGE, AVANT, DEMARAGE, AVANT);
    _delay_ms(DELAY_DEMARAGE);
    _navigator.ajustementPWM(_vitesse, AVANT, _vitesse, AVANT);
}