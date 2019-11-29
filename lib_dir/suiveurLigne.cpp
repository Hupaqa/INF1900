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

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "suiveurLigne.h"
#include "uart.h"

SuiveurLigne::SuiveurLigne(uint8_t vitesse) :
    _vitesse(vitesse)
{
    DDRD |= ((1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7));
    TCNT1 = 0;
    TCCR1A = (1<<COM1A1) | (1<<WGM10) | (1<<COM1B1);
    TCCR1B = (1<<CS11);
    TCCR1C = 0;
};

void SuiveurLigne::ajustementPWM(uint8_t puissanceDroit, DIRECTION directionDroit, uint8_t puissanceGauche, DIRECTION directionGauche)
{
    const uint8_t BOOST_DELAY = 5;

    if (directionDroit == DIRECTION::AVANT)
    {   
        PORTD &= ~(1 << PORTD7);
    }
    else
    {
        PORTD |= (1 << PORTD7);   
    }

    if (directionGauche == DIRECTION::AVANT)
    {
        PORTD &= ~(1 << PORTD6);
    }
    else
    {
        PORTD |= (1 << PORTD6);
    }

    OCR1A = (puissanceDroit) ? UINT8_MAX : 0;
    OCR1B = (puissanceGauche) ? UINT8_MAX : 0;
    _delay_ms(BOOST_DELAY);

    OCR1A = puissanceDroit;
    OCR1B = puissanceGauche;
}

void SuiveurLigne::stopPWM()
{
    OCR1A = 0;
    OCR1B = 0;
}

void SuiveurLigne::avancerDroit()
{
    ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
}

void SuiveurLigne::redressementDroit()
{
    ajustementPWM(BASSE_INTENSITE, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);

};

void SuiveurLigne::redressementGauche()
{ 
    ajustementPWM(_vitesse, DIRECTION::AVANT, BASSE_INTENSITE, DIRECTION::AVANT);
};

void SuiveurLigne::tournerDroit()
{
    ajustementPWM(_vitesse, DIRECTION::ARRIERE, _vitesse, DIRECTION::AVANT);
    while(!(PINC & (1 << EXTREME_DROITE)));
};

void SuiveurLigne::tournerGauche()
{
    ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::ARRIERE);
    while(!(PINC & (1 << EXTREME_GAUCHE)));
};

void SuiveurLigne::virageGaucheCaree()
{
    const uint16_t AVANCER_AVANT_VIRAGE = 1000;

    avancerDroit();
    _delay_ms(AVANCER_AVANT_VIRAGE);
    tournerGauche();
}

bool SuiveurLigne::suivreLigne()
{
    const uint8_t FETCH_DELAY = 75;
    const uint8_t DEBOUNCE_DELAY = 15;

    _delay_ms(FETCH_DELAY);

    if (!suiveurLigneAllume())
    {
        _delay_ms(DEBOUNCE_DELAY);
        if (!suiveurLigneAllume())
        {
            stopPWM();
            return false;
        }
    }
    else if (!(PINC & (1 << MILIEU)))
    {
        if(PINC & (1 << EXTREME_GAUCHE) || PINC & (1 << GAUCHE))
        {
            redressementGauche();
        }
        else if (PINC & (1 << EXTREME_DROITE) || PINC & (1 << DROITE)) 
        {
            redressementDroit();
        }
    }
    else
    {
        avancerDroit();
    }
    return true;
};

bool SuiveurLigne::suiveurLigneAllume()
{
    return (PINC & (1<< EXTREME_GAUCHE) ||
            PINC & (1<< GAUCHE) ||
            PINC & (1<< MILIEU) ||
            PINC & (1<< DROITE) ||
            PINC & (1<< EXTREME_DROITE));
};
