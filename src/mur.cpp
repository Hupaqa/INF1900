#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "mur.h"

// Variables globales pour les interruptions :
// Correspond à la distance entre le robot et le mur.
volatile uint8_t distance = 0;
// Permet de distinguer le début et la fin de l'output du sonar.
volatile bool partirCompteur; 
// S'assure qu'une seule routine d'interruption est exécutée à la réponse du 
// sonar.
volatile bool repondu;

/* 
 *  ISR(INT2_vect)
 *  @param:
 *       INT2_vect : vecteur correspondant à INT2 (PINB2)
 * 
 *  Routine d'interruption appelée lors d'un front montant ou d'un front
 *  descendant sur la PINB2 correspondant à l'output du sonar.
 */
ISR(INT2_vect)
{
    // Interruption lors du front montant qui remet le compteur 2 à zéro et qui
    // active l'interruption en cas d'overflow du compteur 2. 
    if (partirCompteur)
    {
        TCNT2 = 0; // Reinitialise la valeur du compteur
        TIMSK2 |= (1 << TOIE2); // Interrupt on overflow
        partirCompteur = false;
    }
    // Interruption sur le front descendant du sonar. Si le sonar répond avant
    // l'overflow du compteur, la routine calcule la distance entre le mur
    // et le robot. Elle désactive ensuite le le compteur pour s'assurer qu'il
    // n'y a plus d'interruptions à chaque overflow du compteur.
    else if (!repondu)
    {   
        cli(); // Désactive les interruptions
        distance = (TCNT2 * 8) / 58; // 
        TCCR2B = 0; // Desactive le compteur 2
        TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
        repondu = true;
        sei(); // Active les interruptions
    }
}

/* 
 *  ISR(TIMER2_OVF_vect)
 *  @param:
 *       TIMER2_OVF_vect : vecteur correspondant à l'overflow du compteur 2
 * 
 *  Routine d'interruption appelée lorsque le compteur 2 overflow. Cela se
 *  produit lorsque le robot est très loin du mur. Le cas échéance, la routine
 *  fixe la distance à la distance maximale supportée par le compteur 2 pour
 *  que le robot s'approche du mur si et seulement si le sonar n'a pas déjà
 *  répondu précédemment.
 */
ISR(TIMER2_OVF_vect)
{
    if (!repondu)
    {
        cli(); // Désactive les interruptions
        TCCR2B = 0; // Desactive le compteur 2
        TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
        distance = 35; // La distance equivalente a TCNT2 = UINT8_MAX
        repondu = true;
        sei(); // Active les interruptions
    }
}

Mur::Mur(uint8_t vitesse, LCM* lcd) : 
    SuiveurLigne(vitesse), 
    _etat(EtatMur::debutLigne),
    _led(Led()),
    _lcd(lcd),
    _isDone(false)
{
    DDRB |= ((1 << PORTB0) | (1 << PORTB0)); // PORTB0 et PORTB0 en sortie
    DDRC = 0x00; // PINC en entrée
    EICRA |= (1 << ISC20); // Active les interruptions sur les deux fronts de INT2
    _lcd->write("le mur", 0, true);
}

Mur::~Mur()
{
    EICRA &= ~(1 << ISC20); // Désactive les interruptions sur INT2
    EIMSK &= ~(1 << INT2); // Désactive les interruptions sur INT2
    TIMSK2 &= ~(1 << TOIE2); // Interrupt on overflow OFF
    TCCR2B = 0; // Désactive le compteur 2
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
            _isDone = true;
            break;
    }
}

void Mur::enableSonar()
{
    PORTB |= (1 << PORTB4);
    _delay_us(SONAR_DELAY);
    PORTB &= ~(1 << PORTB4);
}

void Mur::fetchSonar()
{
    cli(); // Désactive les interruptions
    partirCompteur = true;
    repondu = false;
    TCCR2B |= (1 << CS22); // Initialise le compteur avec un prescaler de 64
    EIMSK |= (1 << INT2); // Active les interruptions sur INT2
    enableSonar();
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
    avancerDroit();
    _delay_ms(DEPASSER_LIGNE);
    ajustementPWM(_vitesse, DIRECTION::ARRIERE, _vitesse, DIRECTION::AVANT);
    while (!(PINC & (1 << MILIEU)));
}

void Mur::followWall()
{
    fetchSonar();
    while(!repondu);

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