#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "mur.h"
#include "uart.h"

volatile uint8_t distance = 0;
volatile bool repondu;
volatile bool listening;

// Interruption pour le output du sonar
ISR(INT2_vect)
{
    // Reinitialise la valeur du compteur a 0 lors de la premiere interruption
    if (listening)
    {
        TCNT2 = 0; // Reinitialise la valeur du compteur
        TIMSK2 |= (1 << TOIE2); // Interrupt on overflow
        listening = false;

    }
    // Calcule la distance si la reponse precede l'overflow du compteur
    else if (!repondu)
    {   
        cli(); // Stop interrupts
        TCCR2B = 0; // Desactive le compteur 2
        TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
        distance = (TCNT2 * 8) / 58; // Source : documentation
        repondu = true;
        sei();
    }
}

// Interruption lors de l'overflow du compteur
ISR(TIMER2_OVF_vect)
{
    // Prevoit une distance maximale en l'absence d'une reponse du sonar
    if (!repondu)
    {
        cli(); // Desactive les interruptions
        TCCR2B = 0; // Desactive le compteur 2
        TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
        distance = 35; // La distance equivalente a TCNT2 = UINT8_MAX
        repondu = true;
        sei(); // Active les interruptions
    }
}

// Construit l'objet Mur 
Mur::Mur(uint8_t vitesse, LCM* lcd) : 
    SuiveurLigne(vitesse), 
    _etat(EtatMur::debutLigne),
    _led(Led()),
    _lcd(lcd)
{
    DDRB |= ((1 << PORTB0) | (1 << PORTB1)); // Port en sortie pour la led
    EICRA |= (1 << ISC20); // Active les interruptions sur any edge on INT2
    _lcd->write("Le mur", 0, true); // Ecrire sur la led l'etat en cours
}

// Detruit l'objet
Mur::~Mur()
{
    EICRA &= ~(1 << ISC20); // Desactive les interruptions sur INT2
}

void Mur::run()
{
    stayCurrentState = true;
    while(_etat != EtatMur::fin)
    {
        doAction();
        changeState();
    }
}

void Mur::doAction()
{
    switch(_etat)
    {
        case EtatMur::debutLigne:
        case EtatMur::finLigne:
            stayCurrentState = suivreLigne();
            break;
        case EtatMur::suivreMur:
            followWall();
            break;
        case EtatMur::virageDroit:
            tournerDroit();
        case EtatMur::virageGauche:
            tournerGauche();
            break;
        case EtatMur::fin:
            break;
    }
}

void Mur::changeState()
{
    switch(_etat)
    {
        case EtatMur::debutLigne:
            if (!stayCurrentState)
            {
                _etat = EtatMur::suivreMur;
                stayCurrentState = true;
            }
            break;
        case EtatMur::suivreMur:
            if (suiveurLigneAllume())
            {
                _etat = EtatMur::finLigne;
                stayCurrentState = true;
            }
            break;
        case EtatMur::virageDroit:
            _etat = EtatMur::finLigne;
            break;
        case EtatMur::finLigne:
            if (!stayCurrentState)
            {
                _etat = EtatMur::virageGauche;
                stayCurrentState = true;
            }
            break;
        case EtatMur::virageGauche:
            _etat = EtatMur::fin;
            break;
        case EtatMur::fin:
            break;
    }
}

// Active le signal enable du sonar pour 10us
void Mur::enableSonar()
{
    const uint8_t SONAR_DELAY = 10;

    PORTB |= (1 << PORTB4);
    _delay_us(SONAR_DELAY);
    PORTB &= ~(1 << PORTB4);
}

void Mur::fetchSonar()
{
    cli(); // Desactive temporairement les interruptions
    enableSonar();

    listening = true;
    repondu = false;

    TCCR2B |= (1 << CS22); // Initialise le compteur avec un prescaler de 64
    EIMSK |= (1 << INT2); // Active les interruptions sur INT2
    sei(); // Active les interruptions
}

void Mur::moveToWall()
{
    redressementGauche();
    //ajustementPWM(HAUTE_INTENSITE, DIRECTION::AVANT, BASSE_INTENSITE, DIRECTION::AVANT);
}

void Mur::moveAgainstWall()
{
    redressementDroit();
    //ajustementPWM(BASSE_INTENSITE, DIRECTION::AVANT, HAUTE_INTENSITE, DIRECTION::AVANT);
}

void Mur::goStraight()
{
    avancerDroit();
    //ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
}

void Mur::followWall()
{
    const uint8_t DELAY = 40;
    
    fetchSonar();
    while(!repondu); // Attendre la réponse du sonar

    if (distance < 14 && distance > 1)
    {
        moveAgainstWall();
        _led.turnRed();
    }
    else if (distance > 16 && distance < 36)
    {
        moveToWall();
        _led.turnRed();
    }
    else
    {
        goStraight();
        _led.turnGreen();
    }

    _delay_ms(DELAY); // Pour respecter la frequence maximale du sonar
}