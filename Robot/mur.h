#ifndef MUR_H
#define MUR_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

volatile uint8_t distance;
volatile bool repondu;
volatile bool listening;

void init();

void fetch();

void tourner(const uint8_t& distance);


#endif // MUR_H