/*
 * Nom : William Trépanier et Benjamin Theriault 
 * TP6
 * Problème 1
 * Date : 8 octobre 2019
 * Polytechnique Montréal
 * Cours : INF1900
 * Groupe laboratoire : 2


 * Diagramme d'états
+----------------+-----------------+------------------+----------------+----------------------+
|  Current state | interrupt timer | interrupt bouton |   next state   |      couleur led     |
+----------------+-----------------+------------------+----------------+----------------------+
|     ATTENTE    |        X        |         0        |     ATTENTE    |          off         |
+----------------+-----------------+------------------+----------------+----------------------+
|     ATTENTE    |        X        |         1        | INCREMENTATION |          off         |
+----------------+-----------------+------------------+----------------+----------------------+
| INCREMENTATION |        0        |         0        | INCREMENTATION |          off         |
+----------------+-----------------+------------------+----------------+----------------------+
| INCREMENTATION |        X        |         1        |     OUTPUT     |          off         |
+----------------+-----------------+------------------+----------------+----------------------+
| INCREMENTATION |        1        |         X        |     OUTPUT     |          off         |
+----------------+-----------------+------------------+----------------+----------------------+
|     OUTPUT     |        X        |         X        |     ATTENTE    | sequenceClignotement |
+----------------+-----------------+------------------+----------------+----------------------+

* Directives de branchement :
* Bouton : D2
* LED : B0 et B1

*/

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

enum Etat
{
    ATTENTE,
    INCREMENTATION,
    OUTPUT,
};

volatile bool boutonEnfonce = false;
volatile uint8_t compteur = 0;

/*
 * Interrupt lorsque l'on appuie ou l'on relache le bouton.
*/
ISR (INT0_vect)
{
    const uint8_t DEBOUNCE = 30;

    _delay_ms(DEBOUNCE);
    if (PIND & 0x04)
    {
        boutonEnfonce = false;
    }
    else
    {
        boutonEnfonce = true;
    }
    EIFR |= (1 << INTF0);
}

/*
 * Interrupt qui incrémente le compteur.
*/
ISR (TIMER1_COMPA_vect)
{
    compteur++;
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
 * Fait clignoter la lumière une fois sur 500 ms.
*/
void flashRed()
{
    const uint8_t DELAY = 250;

    turnLedRed();
    _delay_ms(DELAY);
    turnLedOff();
    _delay_ms(DELAY);
}

/*
 * Initialise les registres pour qu'il y ait interuption lorsqu'on relache 
 * le bouton.
*/
void initialisationAttente()
{
    EIMSK |= (1 << INT0); // Permet les external interrupts
    EICRA |= (1 << ISC01); // Interrupt on falling edge
    EICRA &= ~(1 << ISC00); // Interrupt on falling edge
    sei(); // Active les interrupts
}

/*
 * Initialise les registres pour qu'il y ait interuption lorsqu'on appuie 
 * sur le bouton. Configure une interuption qui incrémente le compteur à
 * chaque 100ms.
*/
void initialisationIncrementation()
{
    EIMSK |= (1 << INT0); // Permet les external interrupts
    EICRA |= (1 << ISC01) | (1 << ISC00); // Interrupt on rising edge
    TCNT1 = 0; // Initialise le compteur = 0
    compteur = 0;
    OCR1A = 12500; // Permet un interrupt a chaque 100ms
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10); // Prescaler de 64 et CTC
    TIMSK1 |= (1 << OCIE1A); // Active les interrupts
    sei(); // Active les interrupts
}

/*
 * Allume la led verte, puis clignote la led rouge au nombre de compteur/2. Allume
 * ensuite la led verte.
*/
void sequenceClignotement()
{
    turnLedGreen();
    _delay_ms(500);
    turnLedOff();
    _delay_ms(2000);
    compteur /= 0x2;
    for (uint8_t i = 0; i < compteur; i++)
    {
        flashRed();
    }
    turnLedGreen();
    _delay_ms(1000);
    turnLedOff();
}

/*
 * Fait les actions en fonction des états.
*/
void doAction(const Etat& etat)
{
    switch(etat)
    {
    case ATTENTE:
    case INCREMENTATION:
        break;

    case OUTPUT:
        sequenceClignotement();
        break;
    }
}

/*
 * Change d'état selon les conditions.
*/
void changeState(Etat& etat)
{
    switch (etat)
    {
    case ATTENTE:
        if (boutonEnfonce)
        {
            cli();
            etat = Etat::INCREMENTATION;
            initialisationIncrementation();
        }
        break;

    case INCREMENTATION:
        if (!boutonEnfonce || compteur >= 0x78)
        {   
            cli();
            etat = Etat::OUTPUT;
        }
        break;

    case OUTPUT:
        etat = Etat::ATTENTE;
        initialisationAttente();
        break;
    }
}

int main()
{
    DDRD = 0x00; // Port D en entrée
    DDRB = 0xff; // Port B en sortie
    Etat etat = Etat::ATTENTE;
    initialisationAttente();

    while (true)
    {
        doAction(etat);
        changeState(etat);
    }
}