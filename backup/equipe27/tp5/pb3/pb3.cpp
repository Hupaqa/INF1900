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

void initialisationUART ( void ) {

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premier registres pour vous éviter des complications

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    UCSR0B |= (1<<RXEN0) | (1<<TXEN0) ;

    // Format des trames: 8 bits, 1 stop bits, none parity

    UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00) ;
}

void transmissionUART ( uint8_t donnee ) {

    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)));

    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}


int main () {
    DDRA = SORTIE;
    initialisationUART();
    Memoire24CXXX memoire = Memoire24CXXX();

    uint16_t addresse = 0x00;
    //uint8_t donneeEcriture[46] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    uint8_t donneeLecture;

    //memoire.ecriture(addresse, &donneeEcriture[0], 46);

    _delay_ms(5);

    do{
        addresse++;
        memoire.lecture(addresse,&donneeLecture);
        transmissionUART(donneeLecture);
    }while(donneeLecture != 0xFF);
        
    

    return 0;
}