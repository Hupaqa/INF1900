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

#define F_CPU 8000000UL

#include "selection.h"

int main()
{
    LCM lcd(&DDRA, &PORTA); // LCM est copy-protected
    Selection selection(&lcd);
    selection.run();
}

Selection::Selection(LCM* lcd): 
    _etat(EtatSelection::selection),
    _etapeCourrante(EtapesParcours::couloir),
    _lcd(lcd),
    _isDone(false)
{
    DDRD &= ~((1 << BOUTON_BREADBOARD) | (1 << BOUTON_INTERRUPT)); // Pin des boutons en lecture
    _lcd->write("le couloir", 0, true);
}

bool Selection::breadboardDebounced()
{
    const uint8_t DEBOUNCE_DELAY = 15;

    if (!(PIND & (1 << BOUTON_BREADBOARD)))
    {
        _delay_ms(DEBOUNCE_DELAY);
        if (!(PIND & (1 << BOUTON_BREADBOARD)))
        {
            while (!(PIND & (1 << BOUTON_BREADBOARD)));
            return true;
        }
        return false;
    }
    return false;
}

bool Selection::interruptDebounced()
{
    const uint8_t DEBOUNCE_DELAY = 15;

    if (PIND & (1 << BOUTON_INTERRUPT))
    {
        _delay_ms(DEBOUNCE_DELAY);
        if (PIND & (1 << BOUTON_INTERRUPT))
        {
            while (PIND & (1 << BOUTON_INTERRUPT));
            return true;
        }
        return false;
    }
    return false;
}

EtapesParcours Selection::nextStep()
{
    switch(_etapeCourrante)
    {
        case EtapesParcours::couloir:
            return EtapesParcours::mur;
            break;
        case EtapesParcours::mur:
            return EtapesParcours::boucles;
            break;
        case EtapesParcours::boucles:
            return EtapesParcours::coupures;
            break;
        case EtapesParcours::coupures:
            return EtapesParcours::couloir;
            break;
    }
}

void Selection::updateFirstStep()
{
    _etapeCourrante = nextStep();

    switch(_etapeCourrante){
        case(EtapesParcours::couloir):
            _lcd->write("le couloir", 0, true);
            break;
        case(EtapesParcours::mur):
            _lcd->write("le mur", 0, true);
            break;
        case(EtapesParcours::boucles):
            _lcd->write("les deux boucles", 0, true);
            break;
        case(EtapesParcours::coupures):
            _lcd->write("les coupures", 0, true);
            break;
    }
}

void Selection::runStep()
{
    switch(_etapeCourrante)
    {
        case EtapesParcours::couloir:
        {
            Couloir couloir(VITESSE_COULOIR, _lcd);
            couloir.run();
            break;
        }
        case EtapesParcours::mur:
        {
            Mur mur(VITESSE_MUR, _lcd);
            mur.run();
            break;
        }
        case EtapesParcours::boucles:
        {
            Boucle boucle(VITESSE_BOUCLE, _lcd);
            boucle.run();
            break;
        }
        case EtapesParcours::coupures:
        {
            Coupure coupure(VITESSE_COUPURE, _lcd);
            coupure.run();
            break;
        }
    }
}

void Selection::doAction()
{
    switch(_etat)
    {
        case EtatSelection::selection:
            if (breadboardDebounced())
            {
                updateFirstStep();
            }
            break;
        case EtatSelection::appeler:
            for (uint8_t i = 0; i < NOMBRE_ETAPES; ++i)
            {
                runStep();
                _etapeCourrante = nextStep();
            }
            break;
        case EtatSelection::afficherFin:
            {
            SuiveurLigne suiveurLigne(VITESSE_FINALE);
            while (!(PINC & (1 << MILIEU)))
            {
                suiveurLigne.suivreLigne();
            }
            SuiveurLigne::stopPWM();
            _lcd->write("fin", 0, true);
            break;
            }
    }
}

void Selection::changeState()
{
    const uint16_t DELAY_SELECTION = 2000;

    switch(_etat)
    {
        case EtatSelection::selection:
            if (interruptDebounced())
            {
                _etat = appeler;
                _delay_ms(DELAY_SELECTION);
            }
            break;
        case EtatSelection::appeler:
            _etat = EtatSelection::afficherFin;
            break;
        case EtatSelection::afficherFin:
            _isDone = true;
            break;
    }
}

void Selection::run()
{
    while(!_isDone)
    {
        doAction();
        changeState();
    }
}
