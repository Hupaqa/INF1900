#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "couloir.h"

Couloir::Couloir(uint8_t vitesse, LCM* lcd):
    SuiveurLigne(vitesse),
    _etat(EtatCouloir::ligneDebut),
    _lcd(lcd),
    _isDone(false)
{
    DDRC = 0x00; //DDRC en entree
    _lcd->write("Couloir", 0, true);
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
    const uint8_t REDRESSEMENT = 100;

    switch (_etat)
    {
        case EtatCouloir::ligneDebut:
        case EtatCouloir::ligneFin:
            while (suivreLigne());
            break;
        case EtatCouloir::gauche:
            redressementGauche();
            _delay_ms(REDRESSEMENT);
            break;
        case EtatCouloir::droite:
            redressementDroit();
            _delay_ms(REDRESSEMENT);
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
            _etat = EtatCouloir::gauche;
            break;
        case EtatCouloir::gauche:
            if (finCouloir())
            {
                _etat = EtatCouloir::ligneFin;
            }
            else if (PINC & (1 << EXTREME_GAUCHE))
            {
                _etat = EtatCouloir::droite;
            }
            break;
        case EtatCouloir::droite:
            if (finCouloir())
            {
                _etat = EtatCouloir::ligneFin;
            }
            else if (PINC & (1 << EXTREME_DROITE))
            {
                _etat = EtatCouloir::gauche;
            }
            break;
        case EtatCouloir::ligneFin:
            _etat = EtatCouloir::virageFin;
            break;
        case EtatCouloir::virageFin:
            break;
    }
}

bool Couloir::finCouloir()
{
    return !((PINC & (1 << MILIEU)) || (PINC & (1 << GAUCHE)) || (PINC & (1 << DROITE)));
}
