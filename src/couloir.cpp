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

#include "couloir.h"

// Variable globale des interruptions
// Compteur qui détermine si le robot fait un rebond rapide entre la ligne
// latérale et ligne du milieu. Le compteur est initialisé à la limite de
// ce constitue un repond rapide pour ignorer le premier rebond.
volatile uint16_t compteur = Couloir::BOUNCE_RAPIDE;

/* 
 *  ISR(TIMER2_COMPA_vect)
 *  @param:
 *       TIMER2_COMPA_vect : vecteur correspondant à output compare match
 * 
 *  Routine d'interruption appelée à chaque 0.032 seconde qui incrémente le
 *  compteur. 
 */
ISR(TIMER2_COMPA_vect)
{
    ++compteur;
}

Couloir::Couloir(uint8_t vitesse, LCM* lcd):
    SuiveurLigne(vitesse),
    _etat(EtatCouloir::ligneDebut),
    _lcd(lcd),
    _isDone(false)
{
    DDRC = 0x00; //DDRC en entree
    _lcd->write("le couloir", 0, true);
    cli(); // Désactive les interruptions
    TCCR2A |= (1 << WGM21); // Activer le mode CTC
    TCCR2B |= ((1 << CS22) | (1 << CS21) | (1 << CS20)); // Activer compteur prescaler 1024
    OCR2A = 249; // Equivaut a 0.032 sec
    TIMSK2 |= (1 << OCIE2A); // Active les interruptions sur compare match
    sei(); // Active les interruptions
}

Couloir::~Couloir()
{
    cli(); // Désactive les interruptions
    TCCR2A &= ~(1 << WGM21); // Désactive le mode CTC
    TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20)); // Désactive le compteur
    OCR2A = 0; // Réinitialise le output compare register à 0
    TIMSK2 &= ~(1 << OCIE2A); // Désacive les interruptions sur compare match
    sei(); // Active les interruptions
}

void Couloir::run()
{
    while (!_isDone)
    {
        doAction();
        changeState();
    }
}

void Couloir::doAction()
{
    switch (_etat)
    {
        case EtatCouloir::ligneDebut:
        case EtatCouloir::ligneFin:
            while (suivreLigne());
            break;
        case EtatCouloir::limite_gauche:
            devierDroite();
            reinitialiserCompteur();
            while(PINC & (1<< EXTREME_GAUCHE) || PINC & (1<< GAUCHE));
            break;
        case EtatCouloir::avancer_gauche:
            avancerGauche();
            _delay_ms(PWM_REFRESH);
            break;
        case EtatCouloir::limite_droite:
            devierGauche();
            reinitialiserCompteur();
            while(PINC & (1<< EXTREME_DROITE) || PINC & (1<<DROITE));
            break;
        case EtatCouloir::avancer_droite:
            avancerDroite();
            _delay_ms(PWM_REFRESH);
            break;
        case EtatCouloir::virageFin:
            virageGaucheCaree();
            _isDone = true;
            break;
    }
}

void Couloir::changeState()
{
    switch (_etat)
    {
        case EtatCouloir::ligneDebut:
            _etat = EtatCouloir::avancer_droite;
            break;
        case EtatCouloir::limite_gauche:
            _etat = EtatCouloir::avancer_droite;
            break;
        case EtatCouloir::limite_droite:
            _etat = EtatCouloir::avancer_gauche;
            break;
        case EtatCouloir::avancer_gauche:
            if (PINC & (1 << EXTREME_GAUCHE))
            {
                if (compteur < BOUNCE_RAPIDE)
                {
                    _etat = EtatCouloir::ligneFin;
                }
                else
                {
                    _etat = EtatCouloir::limite_gauche;
                }
            }
            else if (finCouloir())
            {
                _etat = EtatCouloir::ligneFin;
            }
            break;
        case EtatCouloir::avancer_droite:
            if (PINC & (1 << EXTREME_DROITE))
            {
                if (compteur < BOUNCE_RAPIDE)
                {
                    _etat = EtatCouloir::ligneFin;
                }
                else
                {
                    _etat = EtatCouloir::limite_droite;
                }
            }
            else if (finCouloir())
            {
                _etat = EtatCouloir::ligneFin;
            }
            break;
        case EtatCouloir::ligneFin:
            _etat = EtatCouloir::virageFin;
            break;
        case EtatCouloir::virageFin:
            break;
    }
}

void Couloir::reinitialiserCompteur()
{
    cli();
    compteur = 0;
    sei();
}

bool Couloir::finCouloir()
{
    return ((PINC & (1 << MILIEU)) || (PINC & (1 << GAUCHE)) || (PINC & (1 << DROITE)));
}

void Couloir::devierGauche()
{
    ajustementPWM(105, DIRECTION::AVANT, 32, DIRECTION::AVANT);
};

void Couloir::devierDroite()
{
    ajustementPWM(32, DIRECTION::AVANT, 105, DIRECTION::AVANT);
}; //145 pour batterie faible (1.446)

void Couloir::avancerGauche()
{
    ajustementPWM(_vitesse, DIRECTION::AVANT, 32, DIRECTION::AVANT);
};
        
void Couloir::avancerDroite()
{
    ajustementPWM(32, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
};


