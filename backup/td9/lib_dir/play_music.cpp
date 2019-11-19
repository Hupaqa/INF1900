#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "play_music.h"

void start_sound (uint8_t note)
{
    TCNT0 = 0;

    OCR0A = (15625/(NOTES[note%45]))-1;
    
    TCCR0A = (1<<COM0A0) | (1<<WGM01);
    TCCR0B = (0<<CS00) | (1<<CS02);
};

void stop_sound ()
{
    TCNT0 = 0;

    OCR0A = 0;
    
    TCCR0A = 0;
    TCCR0B = 0;
};

void play_noir(uint8_t note){
    start_sound(note);
    _delay_ms(250);
    stop_sound();
}

void play_blanche(uint8_t note){
    start_sound(note);
    _delay_ms(500);
    stop_sound();
}

void play_ronde(uint8_t note){
    start_sound(note);
    _delay_ms(1000);
    stop_sound();
}

void play_demitemps(uint8_t note){
    start_sound(note);
    _delay_ms(200);
    stop_sound();
}

void play_note(uint8_t note, uint8_t delais){
    switch(delais){
        case 0: play_noir(note); break;
        case 1: play_blanche(note); break;
        case 2: play_ronde(note); break;
        case 3: play_demitemps(note); break;
    }
}

void play_HarryPotter(){
    uint8_t HarryPotter[30] = {
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
