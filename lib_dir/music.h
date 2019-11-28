#ifndef MUSIC_H
#define MUSIC_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "notes.h"


class Music
{
public:
    Music();
    
    /*
    *  start_sound
    *   
    *  Initialise la minuterie 0 pour produire le son à la fréquence désiré, avec les paramètres suivants:
    *       OCR0A = (15625/(NOTES[note%45]))-1; 
    *            la valeur 15625 vient du calcul suivant : clock du CPU/ (2 * prescaler) = 8 000 000/(2*256)
    *       PWM mode : CTC
    *       Prescaler : 256
    */ 
    void start_sound(uint8_t note);

    /*
    *  stop_sound
    *   
    *  Arrete la minuterie 0
    */ 
    void stop_sound();

    static void play_mario();
    
};

// 
// void play_song(uint8_t notes[], uint8_t delais[]);
// 
// //La playlist
// void play_HarryPotter();

#endif