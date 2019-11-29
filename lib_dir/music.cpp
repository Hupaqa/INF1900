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

