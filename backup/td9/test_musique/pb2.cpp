
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../lib_dir/notes.h"

const int SORTIE = 0xff;
const int ENTREE = 0x00;

void initialisation(){
    DDRB = SORTIE;
    PORTB &= 0b11111011; 
}


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

void fx_sgo (uint8_t note)
{
    TCNT0 = 0;

    OCR0A = (15625/(NOTES[note%45]))-1;
    
    TCCR0A = (1<<COM0A0) | (1<<WGM01);
    TCCR0B = (0<<CS00) | (1<<CS02);
}

void fx_sar ()
{
    TCNT0 = 0;

    OCR0A = 0;
    
    TCCR0A = 0;
    TCCR0B = 0;
}

void play_noir(uint8_t note){
    fx_sgo(note);
    _delay_ms(250);
    fx_sar();
}

void play_blanche(uint8_t note){
    fx_sgo(note);
    _delay_ms(500);
    fx_sar();
}

void play_ronde(uint8_t note){
    fx_sgo(note);
    _delay_ms(1000);
    fx_sar();
}

void play_demitemps(uint8_t note){
    fx_sgo(note);
    _delay_ms(200);
    fx_sar();
}

void play_note(uint8_t note, uint8_t delais){
    switch(delais){
        case 0: play_noir(note); break;
        case 1: play_blanche(note); break;
        case 2: play_ronde(note); break;
        case 3: play_demitemps(note); break;
    }
}

int main () {
    initialisation();
    initialisationUART();

    uint8_t HarryPotter[40] = {
        59, 1, 
        64, 1, 
        67, 3, 
        66, 3, 
        64, 1, 
        71, 3, 
        69, 2, 
        66, 2, 
        64, 0, 
        67, 3,  
        66, 3,  
        63, 1, 
        65, 0, 
        59, 2
    };

    uint8_t i=0;
    while(HarryPotter[i]){
        play_note(HarryPotter[i], HarryPotter[i+1]);
        i += 2;
    }
}