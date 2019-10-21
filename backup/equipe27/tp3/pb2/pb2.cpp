/*
NOMS:
Jordan Lecourtois - 1896164
Hugo Paquin - 1903803

fil : portB pin1 et 2 branche avec JIM2
cavalier : intEN
alimentation avec pws 0.45A et 9V
cable usb
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <util/delay_basic.h>


const uint16_t TEMPS_s = 2;

enum DIRECTION {
    AVANT = 0b00000000,
    ARRIERE = 0b00000010
};


const uint8_t SORTIE = 0x03;
const uint8_t ENTREE = 0x00;

const uint8_t ROUGE = 0x01;
const uint8_t VERT = 0x02;
const uint8_t ETEINT = 0x00;

bool debounce(){
    if ( PIND & 0x04)
    {
        _delay_ms(10);
        if ( PIND & 0x04 )
        {
            return true;
        }
    }
    return false;
}

void delay_cycles(uint32_t cycles){
    const uint16_t MAXCYCLES = 65535; //Propre a la fonction _delay_loop_2
    cycles /= 4; //Propre a la fonction _delay_loop_2

    while(cycles > 0){
       if (cycles > MAXCYCLES){
            _delay_loop_2 (0); 
            cycles-=MAXCYCLES;
        }
        else{
            _delay_loop_2(cycles);
            cycles=0;
        } 
    }
}

void PWM(float ratio, uint32_t cyclesProcesseur_frequence){
    PORTB = PORTB | 0b00000001;
    PORTA = VERT;
    delay_cycles(cyclesProcesseur_frequence*ratio);
    PORTB = PORTB & 0b11111110;
    PORTA = ETEINT;
    delay_cycles(cyclesProcesseur_frequence*(1-ratio));
}



int main () {

    DDRB = SORTIE;
    DDRD = ENTREE; // port D en entree
    PORTB = AVANT; //Direction des moteurs
    DDRA = 0xff;
    
    while (true){
        PORTA = ROUGE;
        while (!debounce());


        uint16_t frequence_Hz = 60;
        uint32_t cyclesProcesseur_frequence = 8000000/frequence_Hz;
        uint16_t cycles_Xs_XHz = frequence_Hz*TEMPS_s;

        for (float ratio = 0; ratio<=1; ratio+=0.25){
        for (uint16_t j = cycles_Xs_XHz; j>0; j--){
            PWM(ratio, cyclesProcesseur_frequence);
            } 
        }

        frequence_Hz = 400;
        cyclesProcesseur_frequence = 8000000/frequence_Hz;
        cycles_Xs_XHz = frequence_Hz*TEMPS_s;

        for (float ratio = 0; ratio<=1; ratio+=0.25){
        for (uint16_t j = cycles_Xs_XHz; j>0; j--){
            PWM(ratio, cyclesProcesseur_frequence);
            } 
        }
    }
}