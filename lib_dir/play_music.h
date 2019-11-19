#ifndef MUSIC_H
#define MUSIC_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "notes.h"

void start_sound (uint8_t note);
void stop_sound ();
void play_noir(uint8_t note);
void play_blanche(uint8_t note);
void play_ronde(uint8_t note);
void play_demitemps(uint8_t note);
void play_note(uint8_t note, uint8_t delais);

//La playlist
void play_HarryPotter();

#endif