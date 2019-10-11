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

enum COLOR {
    ETEINT = 0x00,
    ROUGE = 0x01,
    VERT = 0x02,
    AMBRE
}; 

volatile  bool boutonPoussoir = false;
volatile bool minuterieExpiree = false;


void initialisation ( void ) {
    cli ();

    DDRA = SORTIE; 
    DDRD = ENTREE;

    EIMSK |= (1 << INT0) ;
    EICRA |= (1<<ISC00) ;

    sei ();

}

void partirMinuterie (uint16_t duree){
    minuterieExpiree = false;

    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A = ((1<<COM1A1)|(1<<COM1A0));
    TCCR1B = (1<<CS10)|(1<<CS12);
    TCCR1C = 0;
    TIMSK1 = ((1<<OCIE1A)|(1<<ICIE1));
}

// ISR qui permet l<interruption avec un bouton
ISR(INT0_vect){
    _delay_ms(30);
    boutonPoussoir = true;
}

// ISR qui permet l<interruption avec une minuterie
ISR(TIMER1_COMPA_vect ){
    minuterieExpiree = true;
}

int main () {
    
    initialisation();

    //Attente 2 sec
    _delay_ms(2000);
    
    //Allumer la lumiere 1/10s pour signaler d<appuyer sur le bouton
    PORTA = ROUGE;
    _delay_ms (10);
    PORTA = ETEINT;
    

    //Partie la minuterie
    partirMinuterie(7812);
    
    //Attendre que la minuterie termine ou que l'utilisateur appuie sur le bouton
    do{

    } while (!minuterieExpiree && !boutonPoussoir);
    
    cli();
    
    //Afficher le resultat du test de vitesse
    if(minuterieExpiree)
        PORTA = ROUGE;
    else
        PORTA = VERT;

    sei();
}