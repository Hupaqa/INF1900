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
    _lcd(lcd)
{
    DDRD &= ~((1 << BOUTON_BREADBOARD) | (1 << BOUTON_INTERRUPT)); // Pin des boutons en lecture
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
        case EtapesParcours::couloir:
        {
            Couloir couloir(85, _lcd);
            couloir.run();
            break;
        }
        case EtapesParcours::mur:
        {
            Mur mur(85, _lcd);
            mur.run();
            break;
        }
        case EtapesParcours::boucles:
        {
            Boucle boucle(85, _lcd);
            boucle.run();
            break;
        }
        case EtapesParcours::coupures:
        {
            Coupure coupure(85, _lcd);
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
            _lcd->write("FIN", 0, true);
            break;
        case EtatSelection::finParcours:
            break;
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
            _etat = EtatSelection::finParcours;
            break;
        case EtatSelection::finParcours:
            break;
    }
}

void Selection::run()
{
    _lcd->write("Le couloir", 0, true);

    while(_etat != EtatSelection::finParcours)
    {
        doAction();
        changeState();
    }
}
