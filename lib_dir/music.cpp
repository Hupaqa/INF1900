/*
MIT License
Copyright (c) 2019 
Jordan Lecourtois, Hugo Paquin, William Trépanier, Benjamin Theriault 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "music.h"



ISR(TIMER2_COMPA_vect)
{
    Music::DelaisCourrant--;
    
    if (Music::DelaisCourrant == 0){
        Music::IndexNoteCourrante++;
        Music::play_song(Music::IndexNoteCourrante);
    }
}

Music::Music()
{
    DDRB |= (1 << PINB3) | ( 1<<  PINB5);
    PORTB &= ~(1 << PINB5);

}

Music::~Music(){
    stop_song();
};

void Music::start_sound(uint8_t note)
{
    TCNT0 = 0;

    // clock du CPU/ (prescaler) = 8 000 000/256 = 31250
    const uint16_t CPU_SUR_PRESCALER = 31250;
    OCR0A = (CPU_SUR_PRESCALER/(NOTES[note%45] * 2))-1;
    
    //Toggle on compare match et CTC mode
    TCCR0A = (1<<COM0A0) | (1<<WGM01);

    //Prescaler de 256
    TCCR0B = (1<<CS02);
}

void Music::stop_sound()
{
    TCNT0 = 0;
    OCR0A = 0;  
    TCCR0A = 0;
    TCCR0B = 0;
};

void Music::start_song(){
    cli(); // Désactive les interruptions
    TCCR2A |= (1 << WGM21); // Activer le mode CTC
    TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20)); // Activer compteur prescaler 1024
    OCR2A = 78; // Equivaut a 0.01 sec
    TIMSK2 |= (1 << OCIE2A); // Active les interruptions sur compare match
    sei(); // Active les interruptions

    DelaisCourrant = 0;
    IndexNoteCourrante = 0;

    play_song(IndexNoteCourrante);
}

void Music::play_song(uint8_t indexNote){
    
    DelaisCourrant = FUR_ELISE_DELAIS[indexNote];
    start_sound(FUR_ELISE_NOTE[indexNote]);

};

void Music::stop_song(){
    cli(); // Désactive les interruptions
    TCCR2A &= ~(1 << WGM21); // Désactive le mode CTC
    TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20)); // Désactive le compteur
    OCR2A = 0; // Réinitialise le output compare register à 0
    TIMSK2 &= ~(1 << OCIE2A); // Désacive les interruptions sur compare match
    sei(); // Active les interruptions

    DelaisCourrant = 0;
    IndexNoteCourrante = 0;
}

