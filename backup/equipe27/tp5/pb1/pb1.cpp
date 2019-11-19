/*
NOMS:
Jordan Lecourtois - 1896164
Hugo Paquin - 1903803
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"

const int SORTIE = 0xff;
const int ENTREE = 0x00;

enum COLOR {
    ETEINT = 0x00,
    ROUGE = 0x01,
    VERT = 0x02
}; 


int main () {
    DDRA = SORTIE;
    Memoire24CXXX memoire = Memoire24CXXX();

    uint16_t addresse = 0x00;
    uint8_t donneeEcriture[46] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    uint8_t donneeLecture[46];

    memoire.ecriture(addresse, &donneeEcriture[0], 46);

    _delay_ms(5);

    memoire.lecture(addresse,&donneeLecture[0], 46);

    bool isSame = true;

    for(uint8_t i=0; i<46; i++){
        if(donneeEcriture[i] != donneeLecture[i])
            isSame = false;
    }

    if(isSame)
        PORTA = VERT;
    
    else
        PORTA = ROUGE;

    return 0;
}