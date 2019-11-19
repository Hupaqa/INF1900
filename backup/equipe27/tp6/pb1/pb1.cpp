/*
NOMS:
Jordan Lecourtois - 1896164
Hugo Paquin - 1903803

fil : portB pin1 branche avec positif de la del libre et portB pin2 branche avec negatif de la del libre

Table des etats
╔═══════════════════╦═══════════════════╦════════════════╗
║ etat present      ║ etat suivant      ║ Sortie (LED)   ║
╠═══════════════════╬═══════════════════╬════════════════╣
║ INIT              ║ BUTTON_PRESSED    ║ Eteinte        ║
╠═══════════════════╬═══════════════════╬════════════════╣
║ BUTTON_PRESSED    ║ GREEN_LIGHT_FLASH ║ Eteinte        ║
╠═══════════════════╬═══════════════════╬════════════════╣
║ GREEN_LIGHT_FLASH ║ RED_LIGHT_FLASH   ║ Clignote vert  ║
╠═══════════════════╬═══════════════════╬════════════════╣
║ RED_LIGHT_FLASH   ║ GREEN_LIGHT       ║ Clignote rouge ║
╠═══════════════════╬═══════════════════╬════════════════╣
║ GREEN_LIGHT       ║ INIT              ║ vert           ║
╚═══════════════════╩═══════════════════╩════════════════╝

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
    VERT = 0x02
}; 

enum ETAT {
    INIT, 
    BUTTON_PRESSED,
    GREEN_LIGHT_FLASH,
    RED_LIGHT_FLASH,
    GREEN_LIGHT
};

volatile uint8_t compteurTemps = 0;
volatile bool buttonEvent = false;

volatile ETAT currentState = INIT;
volatile ETAT nextState;

void initialisationBouton ( void ) {
    cli ();
    EIMSK |= (1 << INT0) ;
    EICRA |= (1<<ISC00) ;
    sei ();
}

ISR(INT0_vect){
    _delay_ms (10);

    buttonEvent = true;
}


/*************************************************************************************
**************************************************************************************
**Fonctions et variables qui permettent d'attendre un delais quelconque avec le timer 1
**Fonctions:
**  init_timer1 : initialise le timer1 et calcul le nombre de cycles a effectuer
**  delay_timer1 : effectue le plus grand nombre de cycle que permet timer1 et ajuste delayTimer1_cycles
**  reset_timer1 : arrete le timer1
**  ISR: appelle reset_timer1 ou delay_timer1 dependamment si le temps total est ecoule ou non
**
**Variables:
**  delayTimer1_cycles : nombre de cycle a effectuer pour avoir un delais de duree_ms
**  timer1done : sait si le delais total est termine
**************************************************************************************
**************************************************************************************/
volatile uint32_t delayTimer1_cycles;
volatile bool timer1done;

void delay_timer1(){
    if(delayTimer1_cycles >= UINT16_MAX){
        OCR1A = UINT16_MAX;
        delayTimer1_cycles -= UINT16_MAX;
    }
    else{
        OCR1A = delayTimer1_cycles;
        delayTimer1_cycles = 0;
    }
    TCNT1 = 0;
} 

void init_timer1(uint16_t duree_ms){
    //avec un prescaler de 64, on fait 125 cycles par ms
    const uint8_t CYCLES_PAR_MS = 125; 
    delayTimer1_cycles = CYCLES_PAR_MS*duree_ms;
    timer1done = false;

    TCNT1 = 0;
    TCCR1A |= (1<<COM1A0)|(1<<COM1A1);
    TCCR1B |= (1<<CS10) | (1<<CS11)| (1<<WGM12) ;
    TCCR1C = 0;
    TIMSK1 |= (1<<OCIE1A);

    delay_timer1();
}

void reset_timer1(){
    TCNT1 = 0;
    OCR1A = 0;
    OCR1B = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1C = 0;
}

ISR (TIMER1_COMPA_vect ){
    if(delayTimer1_cycles == 0){
        reset_timer1();
        timer1done = true;
    }
    else {
        delay_timer1();
    }
}
//Fin des fonctions et variables qui permettent d'attendre un delais quelconque avec le timer 1


//Fonction correspondant a l'etat INIT
void initialisationMachineEtat(){
    compteurTemps = 0;
    buttonEvent = false;

    reset_timer1();
    initialisationBouton(); 

    while (!buttonEvent);
    currentState = nextState;
}

//Fonction correspondant a l'etat BUTTON_PRESSED
void fonction_buttonPressed(){
    buttonEvent = false;

    while (compteurTemps < 120 && !buttonEvent){
        init_timer1(100);
        while(!timer1done);
        compteurTemps++;
    }
    currentState = nextState;    
}

//Fonction correspondant a l'etat GREEN_LIGHT_FLASH
void fonction_greenLightFlash(){
    init_timer1(500);
    while (!timer1done){
        PORTB = VERT;
        _delay_ms (25);
        PORTB = ETEINT;
        _delay_ms(25);
    }

    currentState = nextState;
}

//Fonction correspondant a l'etat INIT
void fonction_redLightFlash(){
    //attente initiale de 2s
    _delay_ms (2000);

    compteurTemps /= 2;
    for(uint8_t i = 0; i < compteurTemps; i++){
        PORTB = ROUGE;
        _delay_ms (20);
        PORTB = ETEINT;
        _delay_ms (480); //20+480 = une demi seconde
    }

    currentState = nextState;
}

//Fonction correspondant a l'etat GREEN_LIGHT
void fonction_greenLight(){
    PORTB = VERT;
    _delay_ms (1000);
    PORTB = ETEINT;

    currentState = nextState;
}

//Fonction permettant de changer d'un etat a l'autre
void changerEtat (){
    switch (currentState){
        case INIT : 
            nextState = BUTTON_PRESSED;
            initialisationMachineEtat();
            break;
        case BUTTON_PRESSED :
            nextState = GREEN_LIGHT_FLASH;
            fonction_buttonPressed();
            break;
        case GREEN_LIGHT_FLASH : 
            nextState = RED_LIGHT_FLASH;
            fonction_greenLightFlash();
            break;
        case RED_LIGHT_FLASH : 
            nextState = GREEN_LIGHT;
            fonction_redLightFlash();
            break;
        case GREEN_LIGHT : 
            nextState = INIT;
            fonction_greenLight();
            break;  
    }
}


int main () {

    //Initialisation des entrees
    DDRB = SORTIE;
    DDRD = ENTREE;

    while(true){
        while (currentState != nextState);
        changerEtat();
    }
}
