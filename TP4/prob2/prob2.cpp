/*
 * Nom : William Trépanier et Benjamin Theriault 
 * TP2
 * Problème 2
 * Date : 13 septembre 2019
 * Polytechnique Montréal
 * Cours : INF1900
 * Groupe laboratoire : 2

 * Table des états :
+--------------+----------------+-----------+----------------+
| currentState | input (button) | nextState |  output (LED)  |
+--------------+----------------+-----------+----------------+
| INIT         |        0       | INIT      |  turnLedRed()  |
+--------------+----------------+-----------+----------------+
| INIT         |        1       | AMBER     |  turnLedRed()  |
+--------------+----------------+-----------+----------------+
| AMBER        |        0       | GREEN     | turnLedAmber() |
+--------------+----------------+-----------+----------------+
| AMBER        |        1       | AMBER     | turnLedAmber() |
+--------------+----------------+-----------+----------------+
| GREEN1       |        0       | GREEN1    | turnLedGreen() |
+--------------+----------------+-----------+----------------+
| GREEN1       |        1       | RED       | turnLedGreen() |
+--------------+----------------+-----------+----------------+
| RED          |        0       | OFF       |  turnLedRed()  |
+--------------+----------------+-----------+----------------+
| RED          |        1       | RED       |  turnLedRed()  |
+--------------+----------------+-----------+----------------+
| OFF          |        0       | OFF       |  turnLedOff()  |
+--------------+----------------+-----------+----------------+
| OFF          |        1       | GREEN2    |  turnLedOff()  |
+--------------+----------------+-----------+----------------+
| GREEN2       |        0       | INIT      | turnLedGreen() |
+--------------+----------------+-----------+----------------+
| GREEN2       |        1       | GREEN2    | turnLedGreen() |
+--------------+----------------+-----------+----------------+
*/

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>


/*
 * Liste des états
*/
enum State
{
    INIT_STATE,

};

volatile State currentState = State::INIT_STATE;
volatile uint8_t minuterieExpiree = 0;
volatile uint8_t boutonPoussoir = 0;

/*
 * Affecte la valeur correspondante à la couleur rouge aux pins 0 et 1 du port A. 
*/
void turnLedRed()
{
    PORTA = (PORTA | 0b00000010) & 0b11111110; // set to xxxxxx10
}

/*
 * Affecte la valeur correspondante à la couleur verte aux pins 0 et 1 du port A.
*/
void turnLedGreen()
{
    PORTA = (PORTA | 0b00000001) & 0b11111101; // set to xxxxxx01
}

/*
 * Affecte aucune tension sur les pins 0 et 1 pour fermer la LED.
*/
void turnLedOff()
{
    PORTA &= 0b11111100; // set to xxxxxx00
}

ISR (INT0_vect)
{
    // laisser un delai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms(30);

    // se souvenir ici si le bouton est pressé ou relâché
    if (PIND & 0x04)
    {
        boutonPoussoir = 1;
    }


    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0) ;
}

void initialisation ( void ) {
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli ();

    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA = 0xff; // PORTA to output
    DDRD = 0x00; // PORTD to input

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0) ;

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= 1;

    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}

int main()
{
    initialisation();
    while (true)
    {
        doAction();
    }
}
