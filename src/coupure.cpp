#include "coupure.h"

/*
Coupure::Coupure(int vitesse) : 
    SuiveurLigne(vitesse),
    etatCourant(ETAT_COUPURE::COUPURE1), 
    etatFutur(ETAT_COUPURE::COUPURE1), 
    etatMemoire(ETAT_COUPURE::COUPURE1), 
    isDone(false)
{
    DDRC = 0x00;
    DDRD = 0xff;
    initPWM();
}

bool Coupure::suivreLigne(){
    if(!suiveurLigneAllume()){
        //_delay_ms(20);
        if(!suiveurLigneAllume()){
            //stopPWM();
            return false;
        }
    }else if(PINC & (1 << GAUCHE) || PINC & (1 << EXTREME_GAUCHE)){
        //_delay_ms(20);
        if(PINC & (1 << GAUCHE) || PINC & (1 << EXTREME_GAUCHE)){
            //stopPWM();
            etatMemoire = etatCourant;
            etatFutur = ETAT_COUPURE::REDRESSEMENT_DROIT;
        }    
    }else if(PINC & (1 << DROITE) || PINC & (1 << EXTREME_DROITE)){
        //_delay_ms(20);
        if(PINC & (1 << DROITE) || PINC & (1 << EXTREME_DROITE)){
            //stopPWM();
            etatMemoire = etatCourant;
            etatFutur = ETAT_COUPURE::REDRESSEMENT_GAUCHE;
        }    
    }else
    {
        ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
    }
    return true;
}

void Coupure::redressementDroit()
{
    ajustementPWM(45, DIRECTION::AVANT, _vitesse, DIRECTION::AVANT);
}

void Coupure::redressementGauche(){
    ajustementPWM(_vitesse, DIRECTION::AVANT, 45, DIRECTION::ARRIERE);
}

void Coupure::doAction(){
    switch (etatCourant)
    {
        case ETAT_COUPURE::COUPURE1:
            if(!suivreLigne()){
                etatFutur = ETAT_COUPURE::COUPURE1;
                tournerDroit();
            }
            break;
        case ETAT_COUPURE::COUPURE2:
            if(!suivreLigne()){
                etatFutur = ETAT_COUPURE::COUPURE2;
                tournerGauche();
            }
            break;
        case ETAT_COUPURE::COUPURE3:
            if(!suivreLigne()){
                etatFutur = ETAT_COUPURE::COUPURE3;
                tournerDroit();
            }
            break;
        case ETAT_COUPURE::COUPURE4:
            if(!suivreLigne()){
                etatFutur = ETAT_COUPURE::COUPURE4;
                tournerGauche();
            }
            break;
        case ETAT_COUPURE::FIN:
            if(!suivreLigne()){
                tournerGauche();
                isDone = true;
            }
            break;
        case ETAT_COUPURE::REDRESSEMENT_DROIT:
            redressementDroit();
            if(PINC & (1 << MILIEU))
            {
                etatFutur = etatMemoire; 
            }
            break;   
        case ETAT_COUPURE::REDRESSEMENT_GAUCHE:
            redressementGauche();
            if(PINC & (1 << MILIEU))
            {
                etatFutur = etatMemoire;
            }              
            break;                                                          
    }          

}

void Coupure::run(){
    while(!isDone){
        _delay_ms(50);
        doAction();
        etatCourant = etatFutur;
    }    
}
*/