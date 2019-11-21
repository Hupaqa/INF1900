#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "coupure.h"


Coupure::Coupure(int vitesse, LCM* ecran) : 
    SuiveurLigne(vitesse),
    etatCourant(ETAT_COUPURE::COUPURE1), 
    etatFutur(ETAT_COUPURE::COUPURE1), 
    isDone(false),
    afficheur(ecran)
{
    DDRC = 0x00;
    DDRD = 0xff;
    afficheur->write("Coupure", 0, true);
}

void Coupure::doAction(){
    switch (etatCourant)
    {
        case ETAT_COUPURE::COUPURE1:
            if(!suivreLigne()){
                etatFutur = ETAT_COUPURE::COUPURE2;
                tournerDroit();
            }
            break;
        case ETAT_COUPURE::COUPURE2:
            if(!suivreLigne()){
                etatFutur = ETAT_COUPURE::COUPURE3;
                tournerGauche();
            }
            break;
        case ETAT_COUPURE::COUPURE3:
            if(!suivreLigne()){
                etatFutur = ETAT_COUPURE::COUPURE4;
                tournerDroit();
            }
            break;
        case ETAT_COUPURE::COUPURE4:
            if(!suivreLigne()){
                etatFutur = ETAT_COUPURE::FIN;
                tournerGauche();
            }
            break;
        case ETAT_COUPURE::FIN:
            if(!suivreLigne()){
                tournerGauche();
                isDone = true;
            }
            break;                                                      
    }          

}

void Coupure::run(){
    while(!isDone){
        doAction();
        etatCourant = etatFutur;
    }    
}
