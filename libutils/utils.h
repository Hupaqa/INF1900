#ifndef UTILS_H
#define UTILS_H

#include <avr/io.h>
#include <util/delay.h>

void delay_cycles(uint16_t cycles);

void ajustementPWM (uint8_t puissanceDroit, uint8_t puissanceGauche);

#endif // UTILS_H