#include "coupure.h"

Coupure::Coupure(int vitesse) : 
    SuiveurLigne(vitesse),
    etatCourant(ETAT_COUPURE::COUPURE1), 
    etatFutur(ETAT_COUPURE::COUPURE1), 
    etatMemoire(ETAT_COUPURE::COUPURE1), 
    isDone(false)
{
}

bool Coupure::suivreLigne(){
    if(!suiveurLigneAllume()){
        _delay_ms(20);
        if(!suiveurLigneAllume()){
            stopPWM();
            return false;
        }
    }else if(PINC & (1 << GAUCHE) || PINC & (1 << EXTREME_GAUCHE)){
        _delay_ms(20);
        if(PINC & (1 << GAUCHE) || PINC & (1 << EXTREME_GAUCHE)){
            stopPWM();
            etatMemoire = etatCourant;
            etatFutur = ETAT_COUPURE::REDRESSEMENT_GAUCHE;
        }    
    }else if(PINC & (1 << DROITE) || PINC & (1 << EXTREME_DROITE)){
        _delay_ms(20);
        if(PINC & (1 << DROITE) || PINC & (1 << EXTREME_DROITE)){
            stopPWM();
            etatMemoire = etatCourant;
            etatFutur = ETAT_COUPURE::REDRESSEMENT_DROIT;
        }    
    }else{
        ajustementPWM(_vitesse, 0, _vitesse, 0);
    }
    return true;
}

void Coupure::redressementDroit(){
    ajustementPWM(32, 0, 96, 0);
}

void Coupure::redressementGauche(){
    ajustementPWM(96, 0, 32, 0);
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
            if(PINC & (1 << MILIEU)){
                _delay_ms(20);
                if(PINC & (1 << MILIEU)) etatFutur = etatMemoire;
            }
            break;   
        case ETAT_COUPURE::REDRESSEMENT_GAUCHE:
            redressementGauche();
            if(PINC & (1 << MILIEU)){
                _delay_ms(20);
                if(PINC & (1 << MILIEU)) etatFutur = etatMemoire;
            }              
            break;                                                          
    }          

}
 
void Coupure::changeState(){
    switch (etatCourant)
    {
        case ETAT_COUPURE::COUPURE1:
            etatCourant = etatFutur;
            break;
        case ETAT_COUPURE::COUPURE2:
            etatCourant = etatFutur;
            break;
        case ETAT_COUPURE::COUPURE3:
            etatCourant = etatFutur;
            break;      
        case ETAT_COUPURE::COUPURE4:
            etatCourant = etatFutur;
            break;
        case ETAT_COUPURE::FIN:
            etatCourant = etatFutur;
            break;    
        case ETAT_COUPURE::REDRESSEMENT_DROIT:
            etatCourant = etatFutur;
            break;      
        case ETAT_COUPURE::REDRESSEMENT_GAUCHE:
            etatCourant = etatFutur;
            break;                                                          
    }          

}

void Coupure::run(){
    while(!isDone){
        _delay_ms(20);
        doAction();
        changeState();
    }    
}