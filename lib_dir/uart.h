#ifndef UART_H
#define UART_H

#include <avr/io.h>

/*
*  initialisationUART
*  
*  initialise la transmission UART avec les paramètres suivants:
*       Format des trames: 8 bits, 1 stop bits, none parity
*       2400 bauds.
*/
void initialisationUART();

/*
*  transmissionUART
*  
*  @param : uint8_t donnee: c'est la donnée envoyé par le USART
*
*  Permet de transmettre des données du robot vers l'ordinateur
*  via le cable USB
*/
void transmissionUART(uint8_t donnee);

/*
*  receptionUART
*  
*  @return : uint8_t : c'est la donnée envoyé par le USART
*
*  Permet de transmettre des données de l'ordinateur vers le robot
*/
uint8_t receptionUART();

#endif // UART_H