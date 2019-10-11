/*
 * Nom : William Trépanier et Benjamin Theriault 
 * TP6
 * Problème 2
 * Date : 8 octobre 2019
 * Polytechnique Montréal
 * Cours : INF1900
 * Groupe laboratoire : 2

 * Directive de branchage (débute à 0):
 * LED : B0 et B1
 * Tension analogique : A0
 * Tension AREF : 5V
*/

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "can.h"

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
 * Affecte en alternance les couleurs rouges et vertes pour obtenir la couleur
 * ambre. 
 * 
 * @param   ms   nombre de ms où la DEL est ambrée (max 65535ms)
*/
void turnLedAmber(uint16_t ms)
{
    const double VERY_SHORT_DELAY = 1;
    const double SHORT_DELAY = 3;
    uint16_t nTimes = ms >> 2; // to divize by four

    for (uint16_t i = 0; i < nTimes; i++)
    {
    turnLedRed();
    _delay_ms(VERY_SHORT_DELAY);
    turnLedGreen();
    _delay_ms(SHORT_DELAY); // Add a little more green to achieve amber
    }
}

int main()
{
    DDRB = 0xff; // Port B en sortie
    DDRA = 0x00; // Port A en entrée
    const uint8_t POSITION_LECTURE = 0x00;
    const uint8_t BASSE_INTENSITE = 0x50;
    const uint8_t HAUTE_INTENSITE = 0xB4;
    const uint16_t DELAY_LUMIERE = 12;

    can convertisseur = can();
    uint8_t lecture = convertisseur.lecture(POSITION_LECTURE) >> 2;

    while(true)
    {   
        if (lecture < BASSE_INTENSITE)
        {
            turnLedGreen();
            _delay_ms(DELAY_LUMIERE);
        }
        else if (lecture >= BASSE_INTENSITE && lecture < HAUTE_INTENSITE)
        {
            turnLedAmber(DELAY_LUMIERE);
        }
        else
        {
            turnLedRed();
            _delay_ms(DELAY_LUMIERE);
        }

        lecture = convertisseur.lecture(POSITION_LECTURE) >> 2;
    }   
}