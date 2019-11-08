#ifndef UART_H
#define UART_H

#include <avr/io.h>

void initialisationUART();

void transmissionUART(uint8_t donnee);

uint8_t receptionUART();

#endif // UART_H