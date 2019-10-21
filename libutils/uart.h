#ifndef UART_H
#define UART_H

#include <avr/io.h>

void initialisationUART();

void transmissionUART(uint8_t donnee);

#endif // UART_H