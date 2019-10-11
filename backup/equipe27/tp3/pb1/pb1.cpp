/*
NOMS:
Jordan Lecourtois - 1896164
Hugo Paquin - 1903803

fil : portA pin1 branche avec positif de la del libre et portA pin2 branche avec negatif de la del libre
cavalier : intEN
cable usb
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>

const uint16_t FREQUENCE_Hz = 1000;
const uint16_t CYCLESPROCESSEUR_FREQUENCE = 8000000/FREQUENCE_Hz;
const uint16_t TEMPS_s = 3;
const uint16_t CYCLES_Xs_XHz = FREQUENCE_Hz*TEMPS_s;
const float RATIO_CYCLES = CYCLESPROCESSEUR_FREQUENCE/CYCLES_Xs_XHz;


const uint8_t SORTIE = 0xff;
const uint8_t ENTREE = 0x00;

const uint8_t ETEINT= 0x00;
const uint8_t ROUGE = 0x01;
const uint8_t VERT = 0x02;

void delay_cycles(uint16_t cycles){
    cycles /= 4; //Propre a la fonction _delay_loop_2

    while(cycles > 0){
       if (cycles > UINT16_MAX){
            _delay_loop_2 (0); 
            cycles-=UINT16_MAX;
        }
        else{
            _delay_loop_2(cycles);
            cycles=0;
        } 
    }
}

void PWM(uint16_t cycles, uint8_t couleur){
    PORTA = couleur;
    delay_cycles(cycles);
    PORTA = ETEINT;
    delay_cycles(CYCLESPROCESSEUR_FREQUENCE-cycles);
}



int main () {
    

    DDRA = SORTIE; // port A sortie
    DDRD = ENTREE; // port D en entree

    PORTA = ETEINT;

    while (true)
    {
        
        for (uint16_t a = CYCLES_Xs_XHz; a>0; a--){
            PWM(static_cast<uint16_t>(a*RATIO_CYCLES), VERT); 
        }
        
        for (uint16_t a = CYCLES_Xs_XHz; a>0; a--){
            PWM(static_cast<uint16_t>(a*RATIO_CYCLES), ROUGE); 
        }
    }
}