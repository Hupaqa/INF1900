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
║      OFF     ║    1   ║     ETAT1    ║         0x00        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║     ETAT1    ║    1   ║     ETAT2    ║         0x00        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║     ETAT2    ║    1   ║     ETAT3    ║         0x00        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║     ETAT3    ║    1   ║     ETAT4    ║         0x00        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║     ETAT4    ║    1   ║      ON      ║         0x00        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║      ON      ║    1   ║      OFF     ║         0x01        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║      OFF     ║    0   ║      OFF     ║         0x00        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║     ETAT1    ║    0   ║     ETAT1    ║         0x00        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║     ETAT2    ║    0   ║     ETAT2    ║         0x00        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║     ETAT3    ║    0   ║     ETAT3    ║         0x00        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║     ETAT4    ║    0   ║     ETAT4    ║         0x00        ║
╠══════════════╬════════╬══════════════╬═════════════════════╣
║      ON      ║    0   ║      OFF     ║         0x01        ║
╚══════════════╩════════╩══════════════╩═════════════════════╝
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

enum ETAT {OFF, ETAT1, ETAT2, ETAT3, ETAT4, ON};

const int SORTIE = 0xff;
const int ENTREE = 0x00;

const int ETEINT= 0x00;
const int ROUGE = 0x01;

const int DELAY = 1000;




bool debounce(){
    if ( PIND & 0x04)
    {
        _delay_ms(10);
        if ( PIND & 0x04 )
        {
            while ( PIND & 0x04 );
            return true;
        }
    }
    return false;
}

int main ()
{
    DDRA = SORTIE; // port A sortie
    DDRD = ENTREE; // port D en entree

    ETAT currentState = OFF;
    ETAT nextState = OFF;

    PORTA = ETEINT;

    while (true)
    {
        
        
        switch (currentState){
            case OFF : 
                nextState = ETAT1;
                break;
            case ETAT1 : 
                nextState = ETAT2;
                break;
            case ETAT2 : 
                nextState = ETAT3;
                break;
            case ETAT3 : 
                nextState = ETAT4;
                break;
            case ETAT4 : 
                nextState = ON;
                break;
            case ON:
                PORTA = ROUGE;
                _delay_ms (DELAY);
                PORTA = ETEINT;
                nextState = OFF;
                break;
        }

        while (!debounce() && currentState != ON);
        currentState = nextState;

    }

}