/*
NOMS:
Jordan Lecourtois - 1896164
Hugo Paquin - 1903803

fil : portA pin1 branche avec positif de la del libre et portA pin2 branche avec negatif de la del libre
cavalier : intEN
cable usb

Table de transition de la machine a etat : 
╔══════════════╦════════╦══════════════╦═════════════════════╗
║ ETAT PRESENT ║ BOUTON ║ ETAT SUIVANT ║ SORTIE(COULEUR hex) ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║     INIT     ║    0   ║     INIT     ║         0x01        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║     INIT     ║    1   ║    PRESS1    ║         0X01        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║    PRESS1    ║    0   ║   RELEASE1   ║     0X01 & 0x02     ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║    PRESS1    ║    1   ║    PRESS1    ║     0X01 & 0x02     ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║   RELEASE1   ║    0   ║   RELEASE1   ║         0x02        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║   RELEASE1   ║    1   ║    PRESS2    ║         0x02        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║    PRESS2    ║    0   ║   RELEASE2   ║         0x01        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║    PRESS2    ║    1   ║    PRESS2    ║         0x01        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║   RELEASE2   ║    0   ║   RELEASE2   ║         0x00        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║   RELEASE2   ║    1   ║    PRESS3    ║         0x00        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║    PRESS3    ║    0   ║     INIT     ║         0x02        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║    PRESS3    ║    1   ║    PRESS3    ║         0x02        ║
╚══════════════╩════════╩══════════════╩═════════════════════╝
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

enum ETAT {
    INIT, 
    PRESS1, 
    RELEASE1, 
    PRESS2, 
    RELEASE2, 
    PRESS3
};

volatile uint8_t currentState;
volatile uint8_t nextState = INIT;
volatile uint8_t color = ROUGE;
volatile uint8_t buttonState = PIND & 0x04;
volatile bool statechange = true;


void initialisation ( void ) {

    // cli est une routine qui bloque toutes les interruptions.

    // Il serait bien mauvais d'être interrompu alors que

    // le microcontroleur n'est pas prêt...

    cli ();


    // configurer et choisir les ports pour les entrées

    // et les sorties. DDRx... Initialisez bien vos variables

    DDRA = SORTIE; // port A sortie
    DDRD = ENTREE; // port D en entree


    // cette procédure ajuste le registre EIMSK

    // de l’ATmega324PA pour permettre les interruptions externes

    EIMSK |= (1 << INT0) ;


    // il faut sensibiliser les interruptions externes aux

    // changements de niveau du bouton-poussoir

    // en ajustant le registre EICRA

    EICRA |= (1<<ISC00) ;


    // sei permet de recevoir à nouveau des interruptions.

    sei ();

}


// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR(INT0_vect){
    // laisser un delai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms(30);

    // se souvenir ici si le bouton est pressé ou relâché
    buttonState = PIND & 0x04;

    // changements d'états
    currentState = nextState;

    //si un second signal d'interruption arrive durant l'exécution de ISR, 
    //l'AVR s'en souvient (le bit INTF0 est activé dans le EIFR) et la routine 
    //ISR sera exécutée une seconde fois, une fois la première terminée... 
    //documentation pages 29 à 31
    EIFR |= (1 << INTF0) ;

    statechange = true;
}

int main () {

    initialisation();

    while (true)
    {
        
        if (color == AMBRE){
            while(PIND & 0x04){
                _delay_ms(10);
                PORTA = VERT;
                _delay_ms(10);
                PORTA = ROUGE; 
            }
           
        }else {
            PORTA = color;
        }

        PORTA = color;
        
        if(statechange){
            switch (currentState){
                case INIT : 
                    nextState = PRESS1;
                    color = ROUGE;
                    break;
                case PRESS1 :
                    nextState = RELEASE1;
                    color = AMBRE;
                    break;
                case RELEASE1 : 
                    nextState = PRESS2;
                    color = VERT;
                    break;
                case PRESS2 : 
                    nextState = RELEASE2;
                    color = ROUGE;
                    break;
                case RELEASE2 : 
                    nextState = PRESS3;
                    color = ETEINT;
                    break;
                case PRESS3 : 
                    nextState = INIT;
                    color = VERT;
                    break;
            }
            statechange = false;
        }

    }

}