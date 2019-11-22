#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "mur.h"

volatile uint8_t distance = 0;
volatile bool partirCompteur;
volatile bool repondu;

// Interruption pour le output du sonar
ISR(INT2_vect)
{
    // Reinitialise la valeur du compteur a 0 lors de la premiere interruption
    if (partirCompteur)
    {
        TCNT2 = 0; // Reinitialise la valeur du compteur
        TIMSK2 |= (1 << TOIE2); // Interrupt on overflow
        partirCompteur = false;
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
    _lcd(lcd),
    _isDone(false)
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
    while(!_isDone)
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
            while(suivreLigne());
            break;
        case EtatMur::suivreMur:
            followWall();
            break;
        case EtatMur::virageDroit:
            repositionnerSurLigne();
            break;
        case EtatMur::virageGauche:
            virageGaucheCaree();
            break;
    }
}

void Mur::changeState()
{
    switch(_etat)
    {
        case EtatMur::debutLigne:
            _etat = EtatMur::suivreMur;
            break;
        case EtatMur::suivreMur:
            if (suiveurLigneAllume())
            {
                _etat = EtatMur::virageDroit;
            }
            break;
        case EtatMur::virageDroit:
            _etat = EtatMur::finLigne;
            break;
        case EtatMur::finLigne:
            _etat = EtatMur::virageGauche;
            break;
        case EtatMur::virageGauche:
            stopPWM();
            _isDone = true;
            _lcd->write("fin", 0, true);
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

    partirCompteur = true;
    repondu = false;

    TCCR2B |= (1 << CS22); // Initialise le compteur avec un prescaler de 64
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

void Mur::repositionnerSurLigne()
{
    const uint16_t DEPASSER_LIGNE = 2500;
    const uint8_t POSITIONNER_SUR_LIGNE = 100;

    avancerDroit();
    _delay_ms(DEPASSER_LIGNE);
    ajustementPWM(_vitesse, DIRECTION::ARRIERE, _vitesse, DIRECTION::AVANT);
    while (!(PINC & (1 << MILIEU)));
    avancerDroit();
    _delay_ms(POSITIONNER_SUR_LIGNE);
}

void Mur::followWall()
{
    const uint8_t FETCH_DELAY = 75;
    
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
        avancerDroit();
        _led.turnGreen();
    }

    _delay_ms(FETCH_DELAY);
}