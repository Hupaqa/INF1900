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

Music::Music()
{
    DDRB |= (1 << PINB3) | ( 1<<  PINB5);
    PORTB &= ~(1 << PINB5);
}

void Music::start_sound(uint8_t note)
{
    TCNT0 = 0;

    // clock du CPU/ (2 * prescaler) = 8 000 000/(2*256) = 15625
    OCR0A = (15625/(NOTES[note%45]))-1;
    
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

//void play_song(uint8_t notes[], uint8_t delais[]){
    uint8_t i = 0;

    //while(note[i]){
    //    
    //    i++;
    //}



//}

//void play_HarryPotter(){
//    uint8_t HarryPotter[30] = {
//        59, 1, 
//        64, 1, 
//        67, 3, 
//        66, 3, 
//        64, 1, 
//        71, 3, 
//        69, 2, 
//        66, 2, 
//        64, 0, 
//        67, 3,  
//        66, 3,  
//        63, 1, 
//        65, 0, 
//        59, 2
//    };
//
//    uint8_t i=0;
//    while(HarryPotter[i]){
//        play_note(HarryPotter[i], HarryPotter[i+1]);
//        i += 2;
//    }
//}
//

