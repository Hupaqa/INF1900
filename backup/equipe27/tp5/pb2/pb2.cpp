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



// De l'USART vers le PC

void transmissionUART ( uint8_t donnee ) {

    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)));

    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

int main () {
    DDRA = SORTIE;
    initialisationUART();
    
    char mots[21] = "Le robot en INF1900\n";

    uint8_t i, j;

    for ( i = 0; i < 100; i++ ) {
        for ( j=0; j < 20; j++ ) {
            transmissionUART ( mots[j] );
        }
    }

    PORTA = VERT;
}