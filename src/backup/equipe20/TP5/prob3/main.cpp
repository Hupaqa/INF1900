#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

#include <memoire_24.h>

void initialisationUART() 
{
    // 2400 bauds. Nous vous donnons la valeur des deux
    // premier registres pour vous éviter des complications
    UBRR0H = 0;
    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    // Format des trames: 8 bits, 1 stop bits, none parity
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

// De l'USART vers le PC
void transmissionUART(uint8_t donnee) 
{
    while ( !( UCSR0A & (1<<UDRE0)) )
    {
    }
    UDR0 = donnee;
}

int main()
{
    PORTC = 0x00;
    initialisationUART();

    Memoire24CXXX memoire;
    
    uint16_t adresse = 0;
    uint8_t lecture;
    
    do
    {
        memoire.lecture(adresse, &lecture);
        transmissionUART(lecture);
        adresse++;
    } 
    while (lecture != 0xff);
}