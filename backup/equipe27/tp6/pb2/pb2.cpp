/*
NOMS:
Jordan Lecourtois - 1896164
Hugo Paquin - 1903803

fil : portB pin1 branche avec positif de la del libre et portB pin2 
branche avec negatif de la del libre

Methodologie:
La source de tension a ete mise a 6.5V, le courant maximal a 0.45A et la valeur de AREF 
a ete ajustee a 5V. Nous avons determiner les seuils de facon experimentale
en comparant les valeur obtenu dans le noir, a la luminosite ambiant et
sous une lampe de poche. Nous avons pu observer les valeurs avec la
transmission UART

*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

const int SORTIE = 0xff;
const int ENTREE = 0x00;

enum COLOR {
    ETEINT = 0x00,
    ROUGE = 0x01,
    VERT = 0x02
}; 

enum SEUIL_LUMINOSITE {
    SEUIL_LUMIERE_AMBIANTE = 135,
    SEUIL_LUMIERE_ELEVEE = 245,
};

int main () {
    can newCan = can();

    //Initialisation des entrees
    DDRB = SORTIE;
    DDRA = ENTREE;

    while(true){
        uint8_t intensiteLuminuese = newCan.lecture(0) >> 2;

        if(intensiteLuminuese < SEUIL_LUMIERE_AMBIANTE){
            PORTB = VERT;
        }else if(intensiteLuminuese < SEUIL_LUMIERE_ELEVEE){
            PORTB = VERT;
            _delay_ms(10);
            PORTB = ROUGE;
            _delay_ms(5);
        }else {
            PORTB = ROUGE;
        }
    }
}
