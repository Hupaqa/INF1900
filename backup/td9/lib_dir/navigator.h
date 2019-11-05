#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <avr/io.h>
#include <util/delay.h>

void ajustementPWM (uint8_t puissanceDroit, bool directionDroit, uint8_t puissanceGauche, bool directionGauche);

void turndroite();
void turngauche();

void stopPWM();

#endif // NAVIGATOR_H