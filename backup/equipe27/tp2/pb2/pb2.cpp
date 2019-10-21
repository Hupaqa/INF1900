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

const int SORTIE = 0xff;
const int ENTREE = 0x00;

const int DELAY = 1000;

const int ETEINT= 0x00;
const int ROUGE = 0x01;
const int VERT = 0x02;

enum ETAT {
    INIT, 
    PRESS1, 
    RELEASE1, 
    PRESS2, 
    RELEASE2, 
    PRESS3
};

void buttonEvent(int buttonState){
    _delay_ms(10);
    while (buttonState ==(PIND & 0x04));
}


int main () {
    

    DDRA = SORTIE; // port A sortie
    DDRD = ENTREE; // port D en entree

    ETAT currentState = INIT;
    ETAT nextState = INIT;

    int nextColor = ROUGE;
    PORTA = nextColor;

    while (true)
    {
        
        switch (currentState){
            case INIT : 
                nextState = PRESS1;
                nextColor = ETEINT;
                break;
            case PRESS1 :
                nextState = RELEASE1;
                nextColor = VERT;
                while((PIND & 0x04)) //Tant que le boutton n'est pas relache
                {
                    PORTA = ROUGE;
                    _delay_ms(10);
                    PORTA = VERT;
                    _delay_ms(10);
                }
            case RELEASE1 : 
                nextState = PRESS2;
                nextColor = ROUGE;
                break;
            case PRESS2 : 
                nextState = RELEASE2;
                nextColor = ETEINT;
                break;
            case RELEASE2 : 
                nextState = PRESS3;
                nextColor = VERT;
                break;
            case PRESS3 : 
                nextState = INIT;
                nextColor = ROUGE;
                break;    
        }

        buttonEvent(PIND & 0x04);

        currentState = nextState;
              
        PORTA = nextColor;
        

    }

}