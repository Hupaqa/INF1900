#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "coupure.h"

Coupure::Coupure(int vitesse, LCM* ecran) : 
    SuiveurLigne(vitesse),
    etatCourant(ETAT_COUPURE::COUPURE1), 
    etatFutur(ETAT_COUPURE::COUPURE1), 
    isStateDone(false),
    isDone(false),
    afficheur(ecran)
{
    DDRC = 0x00;
    DDRD = 0xff;
    afficheur->write("Coupure", 0, true);
}

void Coupure::run(){
    while(!isDone){
        doAction();
        changeState();
    }    
}

void Coupure::doAction(){
    switch (etatCourant)
    {
        case ETAT_COUPURE::COUPURE1:
            if(!suivreLigne()){
                isStateDone = true;
                tournerDroit();
            }
            break;
        case ETAT_COUPURE::COUPURE2:
            if(!suivreLigne()){
                isStateDone = true;
                tournerGauche();
            }
            break;
        case ETAT_COUPURE::COUPURE3:
            if(!suivreLigne()){
                isStateDone = true;
                tournerDroit();
            }
            break;
        case ETAT_COUPURE::COUPURE4:
            if(!suivreLigne()){
                isStateDone = true;
                tournerGauche();
            }
            break;
        case ETAT_COUPURE::FIN:
            if(!suivreLigne()){
                isStateDone = true;
                tournerGauche();
                isDone = true;
            }
            break;                                                      
    }          

}

void Coupure::changeState(){
    if (isStateDone){  
        switch (etatCourant)
        {
            case ETAT_COUPURE::COUPURE1:
                etatFutur = ETAT_COUPURE::COUPURE2;
                break;

            case ETAT_COUPURE::COUPURE2:
                etatFutur = ETAT_COUPURE::COUPURE3;
                break;

            case ETAT_COUPURE::COUPURE3:
                etatFutur = ETAT_COUPURE::COUPURE4;
                break;

            case ETAT_COUPURE::COUPURE4:
                etatFutur = ETAT_COUPURE::FIN;
                break;

            case ETAT_COUPURE::FIN:
                break;                                                      
        } 
        isStateDone = false;
        etatCourant = etatFutur;
    }
}


