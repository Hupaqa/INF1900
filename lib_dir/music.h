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

#ifndef MUSIC_H
#define MUSIC_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "notes.h"


class Music
{
public:
    /**
     * Constructeur par défaut
     * 
     * Initialise les pins 3 et 5 du port B en sortie et la pin 5 à 0
     */
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
};

#endif