/*
Pour le suiveur de ligne
U1 = PC3
U2 = PC4
U3 = PC5
U4 = PC6
U5 = PC7

*/

#define F_CPU 8000000UL

#include "suiveurLigne.h"
#include "navigator.h"
#include "delay.h"

uint8_t VITESSE = 96;

enum ETAT {
    INIT,
    COULOIR,
    MUR, 
    COUPURE,
    BOUCLE
};

enum ETAT_BOUCLE{
    INIT
};

enum ETAT_COUPURE{
    DEBUT,
    COUPURE1,
    COUPURE2,
    COUPURE3,
    COUPURE4,
    FIN
}

volatile ETAT etatPresent = ETAT::INIT;
volatile ETAT_BOUCLE etatBoucle = INJT;
volatile ETAT_COUPURE etatCoupure = ETAT_COUPURE::DEBUT;


bool suivreLigne(){
    if (!(PINC & 0b00010000)){
        if(PINC & 0b01000000){
            suiveurLigne::redressementDroit(VITESSE);
        }
        else if (PINC & 0b00000100) {
            suiveurLigne::redressementGauche(VITESSE);
        }
        return true;
    }else if (!(PINC & 0b01111100)){
        ajustementPWM(0, 0, 0, 0)
        return false;
    }
    else{
        ajustementPWM(VITESSE, 0, VITESSE, 0);
        return true;
    }
}

void changeSate(){
    switch(etatPresent){
        case ETAT::INIT :
            etatPresent = COUPURE;
            break;
            
        case ETAT::BOUCLE :
            
            break;
        case ETAT::COUPURE : 
            if(etatCoupure == ETAT_COUPURE::FIN) 
                etatPresent = ETAT::COULOIR;
            break;
        case ETAT::COULOIR : 

            break;
        case ETAT::MUR :
        
            break;    
    }
}

void doAction(){
    switch(etatPresent){
        case ETAT::INIT :
            delay_ms(100);
            break;
        case ETAT::COULOIR :

            break;
        case ETAT::COUPURE :
            actionCoupure();
            break;
        case ETAT::BOUCLE :

            break;
        case ETAT::MUR :

            break;    
    }
}

void actionCoupure(){
    switch(etatCoupure){
        case ETAT_COUPURE::DEBUT :

            break;
        case ETAT_COUPURE::    
    }
}

void actionCouloir(){

    while (PINC & 0b01111100)

    ajustementPWM(VITESSE, 0, VITESSE, 0);
    
    while (!(PINC & 0b00111000))
    {
        if (PINC & 0b01000000) {
            suiveurLigne::redressementDroit(VITESSE);
        }   
        else if (PINC & 0b00000100){
            suiveurLigne::redressementGauche(VITESSE);
        }
    }
}

int main(){
    DDRC = 0x00;
    DDRD = 0xff;


    ajustementPWM(VITESSE, 0, VITESSE, 0);
    while(true){
        suivreLigne();
        delay_ms(5);
    }
    return 0;
}



