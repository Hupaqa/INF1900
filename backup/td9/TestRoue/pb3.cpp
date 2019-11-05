/*
NOMS:
Jordan Lecourtois - 1896164
Hugo Paquin - 1903803
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "bytecode.h"
#include "delay.h"
#include "play_music.h"

uint16_t programCounter = 0;
uint16_t adresseDebutLoop;
uint16_t nbLoopGl;
uint16_t incrementLoop;

const int SORTIE = 0xff;
const int ENTREE = 0x00;

enum DIRECTION {
    AVANT = 0b00000000,
    ARRIERE = 0b00000010
};

void initialisation ( void ) {
    DDRD = SORTIE;// port D en sortie
    DDRB = SORTIE;
    PORTB &= 0b11111011; 
}

int main () {
    
    initialisation();
    delay_ms(1000);
    
    play_HarryPotter();

    fx_trg();
    delay_ms(100);
    fx_tdr();
}