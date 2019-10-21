/*
 * Nom : William Trépanier et Benjamin Theriault 
 * TP2
 * Problème 2
 * Date : 13 septembre 2019
 * Polytechnique Montréal
 * Cours : INF1900
 * Groupe laboratoire : 2

*/

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

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
    _delay_ms(30);
    if (PIND & 0x04)
    {
        boutonPoussoir = 1;
    }

    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0) ;
}

ISR (TIMER1_COMPA_vect)
{
    minuterieExpiree = 1;
}

void partirMinuterie ( uint16_t duree ) {

    minuterieExpiree = 0;

    // interruption après la durée spécifiée

    TCNT1 = 0; // Timer/Counter1
    OCR1A = duree; // Output compare register 1 A
    TCCR1A = 0; // timer/counter control register A
    TCCR1B |= (1 << CS12); // timer/counter control register B
    TCCR1C = 0; // timer/counter control register A
    TIMSK1 |= (1 << OCIE1A); // Timer/Counter1 Interrupt Mask Register
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
    EIMSK |= (1 << INT0)
    ;

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
    _delay_ms(10000);
    turnLedRed();
    _delay_ms(100);
    turnLedOff();
    partirMinuterie(31250);
    while ( minuterieExpiree == 0 && boutonPoussoir == 0 );
    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli ();
    // Verifier la réponse
    if(boutonPoussoir == 1){
        turnLedGreen();
    }else{
        turnLedRed();
    }
}
