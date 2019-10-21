/*
NOMS:
Jordan Lecourtois - 1896164
Hugo Paquin - 1903803
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


const int SORTIE = 0xff;
const int ENTREE = 0x00;

enum DIRECTION {
    AVANT = 0b00000000,
    ARRIERE = 0b00000010
};

enum COLOR {
    ETEINT = 0x00,
    ROUGE = 0x01,
    VERT = 0x02,
    AMBRE
}; 



void initialisation ( void ) {
    cli ();


    DDRA = SORTIE; // port A sortie
    DDRD = SORTIE;// port D en sortie
    
    sei ();

}


void ajustementPWM (float ratioDroit, float ratioGauche){
    TCNT1 = 0;

    OCR1A = static_cast<uint8_t>(ratioDroit*UINT8_MAX);
    OCR1B = static_cast<uint8_t>(ratioGauche*UINT8_MAX);
    

    TCCR1A = ((1<<COM1A1)|(1<<WGM10)|(1<<COM1B1));
    TCCR1B = (1<<CS11);
    TCCR1C = 0;
}

int main () {
    
    initialisation();

    ajustementPWM(0,0);
    _delay_ms(2000);

    ajustementPWM(0.25,0.25);
    _delay_ms(2000);

    ajustementPWM(0.50,0.50);
    _delay_ms(2000);

    ajustementPWM(0.75,0.75);
    _delay_ms(2000);

    ajustementPWM(1,1);
    _delay_ms(2000);

    ajustementPWM(0,0);
}