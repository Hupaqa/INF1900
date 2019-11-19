#define F_CPU 8000000UL

#include "mur.h"
#include "uart.h"

volatile uint8_t distance = 0;
volatile bool repondu;
volatile bool listening;

// Interruption pour le output du sonar
ISR(INT2_vect)
{
    if (listening)
    {
        TCNT2 = 0; // Reinitialise la valeur du compteur
        TIMSK2 |= (1 << TOIE2); // Interrupt on overflow
        listening = false;

    }
    else if (!repondu)
    {   
        cli(); // Stop interrupts
        TCCR2B = 0;
        TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
        distance = (TCNT2 * 8) / 58;
        repondu = true;
        sei();
    }
}

// Interruption lors de l'overflow du compteur
ISR(TIMER2_OVF_vect)
{
    if (!repondu)
    {
        cli();
        TCCR2B = 0;
        TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
        distance = 35;
        repondu = true;
        sei();
    }
}

Mur::Mur(uint8_t vitesse) : 
    SuiveurLigne(vitesse), 
    _etat(EtatMur::debutLigne),
    _led(Led())
{
    // Initialisation du compteur
    TCCR2B |= (1 << CS22); // Prescaler de 64
    // Interruption 
    EICRA |= (1 << ISC20); // Any edge
    // Initialisation PWM
    initPWM(); 
}

void Mur::run()
{
    bool stayCurrentState = true;
    while(_etat != EtatMur::fin)
    {
        stayCurrentState = doAction();
        changeState(stayCurrentState);
    }
}

bool Mur::doAction()
{
    switch(_etat)
    {
        case (EtatMur::debutLigne):
        case (EtatMur::finLigne):
        {
            bool statut = suivreLigne();
            return statut;
        }
        case (EtatMur::mur):
        {
            followWall();
            return true;
        }
        case (EtatMur::virage):
        {
            return true;
        }
    }
}

void Mur::changeState(bool stayCurrentState)
{
    switch(_etat)
    {
        case (EtatMur::debutLigne):
            if (!stayCurrentState)
            {
                _etat = EtatMur::mur;
            }
            break;
        case (EtatMur::mur):
            if (suiveurLigneAllume())
            {
                _etat = EtatMur::finLigne;
            }
            break;
        case (EtatMur::finLigne):
            if (!stayCurrentState)
            {
                _etat = EtatMur::virage;
            }
            break;
        case (EtatMur::virage):
            if (suiveurLigneAllume())
            {
                _etat = EtatMur::fin;
            }
    }
}

void Mur::fetchSonar()
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

void Mur::moveToWall()
{
    ajustementPWM(HAUTE_INTENSITE, DIRECTION::AVANT, BASSE_INTENSITE, DIRECTION::AVANT);
}

void Mur::moveAgainstWall()
{
    ajustementPWM(BASSE_INTENSITE, DIRECTION::AVANT, HAUTE_INTENSITE, DIRECTION::AVANT);
}

void Mur::goStraight()
{
    ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
}

void Mur::followWall()
{
    const uint8_t DELAY = 50;
    fetchSonar();

    while(!repondu); // Attendre la réponse du sonar
    if (distance < 13 && distance > 1)
    {
        moveAgainstWall();
        _led.turnRed();
    }
    else if (distance > 17 && distance < 36)
    {
        moveToWall();
        _led.turnRed();
    }
    else
    {
        goStraight();
        _led.turnGreen();
    }
    transmissionUART(distance);
    _delay_ms(DELAY); // Pour respecter la frequence maximale du sonar
}