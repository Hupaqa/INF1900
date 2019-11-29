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