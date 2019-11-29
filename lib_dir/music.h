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

    /**
     * Destructeur
     * 
     * Désinitialise les compteurs et les interruptions
     */ 
    ~Music();
    
    /*
    *  start_sound
    *   
    *  Initialise la minuterie 0 pour produire le son à la fréquence désiré, avec les paramètres suivants:
    *       OCR0A = (15625/(NOTES[note%45]))-1; 
    *            la valeur 15625 vient du calcul suivant : clock du CPU/ (2 * prescaler) = 8 000 000/(2*256)
    *       PWM mode : CTC
    *       Prescaler : 256
    */ 
    static void start_sound(uint8_t note);

    /*
    *  stop_sound
    *   
    *  Arrete la minuterie 0
    */ 
    void stop_sound();

    void initialisationTimer2();

    void start_song();

    static void play_song(uint8_t indexNote);

    void stop_song();

    //static void play_mario();
    

    static volatile uint8_t DelaisCourrant;
    static volatile uint8_t IndexNoteCourrante;
    
};


//La playlist
static const uint16_t FUR_ELISE_NOTE[] = {
    E4, Dd4, E4, Dd4, E4, B3, D4, C4, A3,
    C3, E3, A3, B3, E3, Gd3, B3, C4, E3,
    E4, Dd4, E4, Dd4, E4, B3, D4, C4, A3,
    C3, E3, A3, B3, E3, C4, B3, A3

};
static const uint8_t FUR_ELISE_DELAIS[] = {
    (uint8_t)DUREE_NOTE::DEMI_NOIR, 
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR, 
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR, 
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR, 
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR, 
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR, 
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR, 
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR,
    (uint8_t)DUREE_NOTE::DEMI_NOIR
};


#endif