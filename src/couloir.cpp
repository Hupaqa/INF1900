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
        case EtatCouloir::limite_gauche:
            devierDroite();
            _delay_ms(REDRESSEMENT);
            break;
        case EtatCouloir::avancer_gauche:
            avancerGauche();
            _delay_ms(REDRESSEMENT >> 1);
            break;
        case EtatCouloir::limite_droite:
            devierGauche();
            _delay_ms(REDRESSEMENT);
            break;
        case EtatCouloir::avancer_droite:
            avancerDroite();
            _delay_ms(REDRESSEMENT >> 1);
            break;
        case EtatCouloir::virageFin:
            virageGaucheCaree();
            _isDone = true;
            break;
    }
}

void Couloir::changeState()
{
    const uint8_t DEBOUNCE = 25;

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
            /*
            if (finCouloir())
            {
                _delay_ms(DEBOUNCE);
                if(finCouloir()) {
                    _etat = EtatCouloir::ligneFin;
                    break;
                }
            }
            
            if (PINC & (1 << EXTREME_GAUCHE))
            {
                _etat = EtatCouloir::droite;
            }
            */
        case EtatCouloir::avancer_gauche:
            if (finCouloir())
            {
                _etat = EtatCouloir::ligneFin;
            }
            if (PINC & (1 << EXTREME_GAUCHE))
            {
                _etat = EtatCouloir::limite_gauche;
            }
            break;
        case EtatCouloir::avancer_droite:
            if (finCouloir())
            {
                _etat = EtatCouloir::ligneFin;
            }
            if (PINC & (1 << EXTREME_DROITE))
            {
                _etat = EtatCouloir::limite_gauche;
            }
            break;
        /*
        case EtatCouloir::droite:
            _etat = EtatCouloir::avancer;
            
            if (finCouloir())
            {
                _delay_ms(DEBOUNCE);
                if(finCouloir()) {
                    _etat = EtatCouloir::ligneFin;
                    break;
                }
            }
            
            if (PINC & (1 << EXTREME_DROITE))
            {
                _etat = EtatCouloir::gauche;
            }
            
            break;
            */
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

void Couloir::devierGauche()
{
    ajustementPWM(125, DIRECTION::AVANT, 0, DIRECTION::AVANT);
};

void Couloir::devierDroite()
{
    ajustementPWM(0, DIRECTION::AVANT, 125, DIRECTION::AVANT);
};

void Couloir::avancerGauche(){
    redressementGauche();
};
        
void Couloir::avancerDroite(){
    redressementDroit();
};
