#define F_CPU 8000000UL

#include "selection.h"

int main()
{
    LCM lcd(&DDRA, &PORTA);
    Selection selection(&lcd);
    selection.run();
}

Selection::Selection(LCM* lcd): 
    _etat(EtatSelection::selection),
    _etapeCourrante(EtapesParcours::couloir),
    _lcd(lcd)
{
}

bool Selection::breadboardDebounced()
{
    const uint8_t DEBOUNCE_DELAY = 15;

    if (!(PORTD & (1 << BOUTON_BREADBOARD)))
    {
        _delay_ms(DEBOUNCE_DELAY);
        if (!(PORTD & (1 << BOUTON_BREADBOARD)))
        {
            return true;
        }
        return false;
    }
    return false;
}

bool Selection::interruptDebounced()
{
    const uint8_t DEBOUNCE_DELAY = 15;

    if (PORTD & (1 << BOUTON_INTERRUPT))
    {
        _delay_ms(DEBOUNCE_DELAY);
        if (PORTD & (1 << BOUTON_INTERRUPT))
        {
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
            _lcd->write("Le couloir", 0, true);
            break;
        case(EtapesParcours::mur):
            _lcd->write("Le mur", 0, true);
            break;
        case(EtapesParcours::boucles):
            _lcd->write("Les deux boucles", 0, true);
            break;
        case(EtapesParcours::coupures):
            _lcd->write("Les coupures", 0, true);
            break;
    }
}


void Selection::runStep()
{
    switch(_etapeCourrante)
    {
        case(EtapesParcours::couloir):
        {
            Couloir couloir(75);
            couloir.run();
            break;
        }
        case(EtapesParcours::mur):
        {
            Mur mur(75);
            mur.run();
            break;
        }
        case(EtapesParcours::boucles):
        {
            Boucle boucle(75);
            boucle.run();
            break;
        }
        case(EtapesParcours::coupures):
        {
            Coupure coupure(75);
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
            for (uint8_t i = 0; i < nombreEtapes; ++i)
            {
                runStep();
                _etapeCourrante = nextStep();
            }
            break;
        case EtatSelection::afficherFin:
            _lcd->write("FIN", 0, true);
            break;
        case EtatSelection::fin:
            break;
    }
}

void Selection::changeState()
{
    switch(_etat)
    {
        case EtatSelection::selection:
            if (interruptDebounced())
            {
                _etat = appeler;
            }
            break;
        case EtatSelection::appeler:
            _etat = EtatSelection::afficherFin;
            break;
        case EtatSelection::afficherFin:
            _etat = EtatSelection::fin;
            break;
        case EtatSelection::fin:
            break;
    }
}

void Selection::run()
{
    while(_etat != EtatSelection::fin)
    {
        doAction();
        changeState();
    }
}
