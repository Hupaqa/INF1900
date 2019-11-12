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

enum ETAT {
    INIT,
    COULOIR,
    MUR, 
    COUPURE,
    BOUCLE
};

enum ETAT_COUPURE{
    TOUR_DROIT_1,
    TOUR_GAUCHE_1,
    TOUR_DROIT_2,
    TOUR_GAUCHE_2
};

volatile ETAT etatPresent = COULOIR;

/*ETAT etatInitial() {
    return INIT;
}*/

void suivreLigne(){
    if (!(PINC & 0b00010000)){
        if ((PINC & 0b00010000)&&(PINC & 0b00001000)&&(PINC & 0b00000100)){
            suiveurLigne::tournerGauche();
        }else if(PINC & 0b01000000){
            suiveurLigne::redressementDroit();
        }
        else if (PINC & 0b00000100) {
            suiveurLigne::redressementGauche();
        }
    }else if ((PINC & 0b00001000)&&(PINC & 0b00000100)){
        suiveurLigne::tournerGauche();
    }
    else{
        ajustementPWM(128, 0, 128, 0);
    }
}





int main(){
    DDRC = 0x00;
    DDRD = 0xff;


    ajustementPWM(128, 0, 128, 0);
    while(true){
        suivreLigne();
        delay_ms(5);
    }
    return 0;
}



