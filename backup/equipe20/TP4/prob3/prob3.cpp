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

void ajustementPWM (uint8_t ratioRoueA, uint8_t ratioRoueB) 
{
    const uint8_t maxCount = 0xFF;
    // mise à un des sorties OC1A et OC1B sur comparaison
    // réussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe à 0xFF (mode #1 de la table 17-6
    // page 177 de la description technique du ATmega324PA)
    OCR1A = (maxCount/0x64) * ratioRoueA;
    OCR1B = (maxCount/0x64) * ratioRoueB;

    TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B |= (1 << CS11); 
    TCCR1C = 0;
}

int main()
{
    DDRD = 0xff;
    ajustementPWM(25, 25);
    while(true)
    {
    }
}