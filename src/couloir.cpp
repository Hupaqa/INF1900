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
    const uint16_t REDRESSEMENT = 500;

    switch (_etat)
    {
        case EtatCouloir::ligneDebut:
        case EtatCouloir::ligneFin:
            while (suivreLigne());
            break;
        case EtatCouloir::limite_gauche:
            devierDroite();
            while(PINC & (1<< EXTREME_GAUCHE) || PINC & (1<< GAUCHE))
            {
                if(PINC & (1<< EXTREME_DROITE))
                {
                    _etat = ligneFin;
                }
            }
            break;
        case EtatCouloir::avancer_gauche:
            avancerGauche();
            _delay_ms(REDRESSEMENT);
            break;
        case EtatCouloir::limite_droite:
            devierGauche();
            while(PINC & (1<< EXTREME_DROITE) || PINC & (1<<DROITE))
            {
                if(PINC & (1<< EXTREME_GAUCHE))
                {
                    _etat = ligneFin;
                }
            }
            break;
        case EtatCouloir::avancer_droite:
            avancerDroite();
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
            if (PINC & (1 << EXTREME_GAUCHE))
            {
                _etat = EtatCouloir::limite_gauche;
            }
            else if (finCouloir())
            {
                _etat = EtatCouloir::ligneFin;
            }
            break;
        case EtatCouloir::avancer_droite:
            if (PINC & (1 << EXTREME_DROITE))
            {
                _etat = EtatCouloir::limite_droite;
            }
            else if (finCouloir())
            {
                _etat = EtatCouloir::ligneFin;
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
    return ((PINC & (1 << MILIEU)) || (PINC & (1 << GAUCHE)) || (PINC & (1 << DROITE)));
}

void Couloir::devierGauche()
{
    ajustementPWM(_vitesse, DIRECTION::AVANT, 60, DIRECTION::AVANT);
};

void Couloir::devierDroite()
{
    ajustementPWM(60, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
};

void Couloir::avancerGauche()
{
    ajustementPWM(_vitesse, DIRECTION::AVANT, 80, DIRECTION::AVANT);
};
        
void Couloir::avancerDroite()
{
    ajustementPWM(80, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
};


