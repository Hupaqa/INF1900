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

#ifndef LED_H
#define LED_H

#include <avr/io.h>

class Led {
public:
    /*
     *  Constructeur par défaut
     * 
     *  Initialise le data direction register pour que PINB0 (+) et PINB1 (-) 
     *  soient en sortie pour la LED.
     */
    Led();

    /*
     *  turnRed
     * 
     *  Configure PINB0 (+) et PINB1 (-) pour que la LED soit rouge.
     */
    void turnRed();

    /*
     *  turnRed
     * 
     *  Configure PINB0 (+) et PINB1 (-) pour que la LED soit verte.
     */
    void turnGreen();

    /*
     *  turnRed
     * 
     *  Configure PINB0 (+) et PINB1 (-) pour que la LED soit éteinte.
     */
    void turnOff();
};

#endif //DEL_H