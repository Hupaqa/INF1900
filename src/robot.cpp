/*
Pour le suiveur de ligne
U1 = PC3
U2 = PC4
U3 = PC5
U4 = PC6
U5 = PC7

*/

#define F_CPU 8000000UL
#define ddr_lcd DDRA
#define port_lcd PORTA

#include "suiveurLigne.h"
#include "navigator.h"
#include "delay.h"
#include "play_music.h"
#include "uart.h"
#include "display.h"

#include "customprocs.h"
#include "mur.h"

uint8_t VITESSE = 100;

/*
enum ETAT {
    INIT,
    COULOIR,
    MUR, 
    COUPURE,
    BOUCLE
};

enum ETAT_COUPURE{
    DEBUT_COUPURE,
    COUPURE1,
    COUPURE2,
    COUPURE3,
    COUPURE4,
    COUPURE_FIN
};

enum ETAT_MUR{
    DEBUT_MUR,
    MUR_ACTION,
    FIN_MUR
};

enum ETAT_BOUCLE {
    ALLER_GROSSE_BOUCLE,
    FAIRE_BOUCLE,
    FIN_BOUCLE
};

enum ETAT_COULOIR {
    DEBUT_COULOIR,
    ACTION_COULOIR,
    FIN_COULOIR
};

LCM ecriture(&ddr_lcd, &port_lcd);

volatile ETAT etatPresent = COUPURE;
volatile ETAT_BOUCLE etatBoucle = ALLER_GROSSE_BOUCLE;
volatile ETAT_COUPURE etatCoupure = DEBUT_COUPURE;
volatile ETAT_MUR etatMur = DEBUT_MUR;
volatile ETAT_COULOIR etatCouloir = DEBUT_COULOIR;

#define MILIEU PINC4
#define GAUCHE PINC5
#define GGAUCHE PINC6
#define DROITE PINC3
#define DDROITE PINC2

bool suivreLigne(){
    uint8_t vitesse = 88;//Vitesse determine experimentalement
    SuiveurLigne suiveurLigne(vitesse); 
    Navigator navigator();

    _delay_ms(50);
    if (!(PINC & 0b01111100))
    {
        _delay_ms(25);
        if (!(PINC & 0b01111100))
        {
            navigator.ajustementPWM(0, 0, 0, 0);
            return false;
        }
        return true;
    }
    else if (!(PINC & (1 << MILIEU)))
    {
        if(PINC & ((1 << GGAUCHE) | (1 << GAUCHE)) || PINC & (1 << GGAUCHE))
        {
            suiveurLigne.redressementDroit();
        }
        else if (PINC & ((1 << DDROITE) | (1 << DROITE) || PINC & (1 << DDROITE))) 
        {
            suiveurLigne.redressementGauche();
        }
        return true;
    }
    else
    {
        navigator.ajustementPWM(VITESSE, 0, VITESSE, 0);
        return true;
    }
}

bool suivreCouloir(){
    delay_ms(10);
    if(PINC & (1 << GGAUCHE)){
        suiveurLigne::redressementDroit(VITESSE);
    }else if(PINC & (1 << DDROITE)){
        suiveurLigne::redressementGauche(VITESSE);
    }else if(PINC & ((1 << MILIEU) || PINC & (1 << GAUCHE)) || PINC & (1 << DROITE)){
        delay_ms(10);
        if(PINC & ((1 << MILIEU) || PINC & (1 << GAUCHE)) || PINC & (1 << DROITE))
            return false;
    }
    ajustementPWM(255, 0, 255, 0);
    _delay_ms(5);
    ajustementPWM(VITESSE, 0, VITESSE, 0);
    return true;
}

void actionCoupure(){
    switch(etatCoupure){
        case DEBUT_COUPURE :
            ecriture.write("DEBUT_COUPURE", 0, true);
            while(suivreLigne());
            etatCoupure = COUPURE1;
            break;
        case COUPURE1 :
            ecriture.write("COUPURE1", 0, true);
            start_sound(81);
            suiveurLigne::tournerDroit(VITESSE);
            stop_sound();
            while(suivreLigne());
            etatCoupure = COUPURE2;
            break;   
        case COUPURE2 :
            ecriture.write("COUPURE2", 0, true);
            start_sound(45);
            suiveurLigne::tournerGauche(VITESSE);
            stop_sound();
            while(suivreLigne());
            etatCoupure = COUPURE3;
            break;  
        case COUPURE3 :
            ecriture.write("COUPURE3", 0, true);
            start_sound(81);
            suiveurLigne::tournerDroit(VITESSE);
            stop_sound();
            while(suivreLigne());
            etatCoupure = COUPURE4;
            break;
        case COUPURE4 :
            ecriture.write("COUPURE4", 0, true); 
            start_sound(45);
            suiveurLigne::tournerGauche(VITESSE);
            stop_sound();
            while(suivreLigne());
            etatCoupure = COUPURE_FIN;
            break;     
        case COUPURE_FIN :
            ecriture.write("COUPURE_FIN", 0, true);
            while(suivreLigne());
            suiveurLigne::tournerGauche(VITESSE);
            break;                                      
    }
}

void actionCouloir(){
    switch (etatCouloir)
    {
        case DEBUT_COULOIR :
            ecriture.write("DEBUT_COULOIR", 0, true);
            while (suivreLigne());
            etatCouloir = ACTION_COULOIR;
            break;
        case ACTION_COULOIR :
            ecriture.write("ACTION_COULOIR", 0, true);
            while(suivreCouloir());
            etatCouloir = FIN_COULOIR;
            break;
        case FIN_COULOIR :
            ecriture.write("FIN_COULOIR", 0, true);
            while(suivreLigne());
            suiveurLigne::tournerGauche(VITESSE);
            break;
    }
    while (suivreLigne());

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
    while (suivreLigne());
    suiveurLigne::tournerGauche(VITESSE);
}

void actionMur(){
    switch(etatMur){
        case DEBUT_MUR :
            while(suivreLigne());
            etatMur = MUR_ACTION;
            break;
        case MUR_ACTION :
            //CODE AVEC LE SONORE
            etatMur = FIN_MUR;
            break;
        case FIN_MUR :
            while(suivreLigne());
            suiveurLigne::tournerGauche(VITESSE);
            break;
    }
}

void actionBoucle(){
    switch(etatBoucle){
        case ALLER_GROSSE_BOUCLE : 
        {
            uint8_t nIntersections = 0;
            while(nIntersections != 2){
                if((PINC & 0b01000000)&&(PINC & 0b00100000)&&(PINC & 0b00010000)) {
                    nIntersections++;
                }
                suivreLigne();
            }
            etatBoucle = FAIRE_BOUCLE;
            break;
        }
        case FAIRE_BOUCLE: 
            for(uint8_t j = 0; j <2; j++){
                while((PINC & 0b01000000)&&(PINC & 0b00100000)&&(PINC & 0b00010000)){
                    suivreLigne();
                }
                suiveurLigne::tournerGauche(VITESSE);

                for (uint8_t i=0; i != 3; i++){
                    while(suivreLigne());
                    suiveurLigne::tournerGauche(VITESSE);
                }
            }
            etatBoucle = FIN_BOUCLE;
            break;

        case FIN_BOUCLE: 
            while(suivreLigne());
            suiveurLigne::tournerGauche(VITESSE);            
            break;
    }
}

void changeState(){
    switch(etatPresent){
        case INIT :
            etatPresent = COUPURE;
            break;
            
        case BOUCLE :
            if(etatBoucle == FIN)
                etatPresent = COUPURE;
            break;
        case COUPURE : 
            if(etatCoupure == COUPURE_FIN) 
                etatPresent = COULOIR;
            break;
        case COULOIR : 
            if(etatCouloir == FIN_COULOIR)
                etatPresent = MUR;
            break;
        case MUR :
            if(etatMur == FIN)
                etatPresent = BOUCLE;
            break;    
    }
}

void doAction(){
    switch(etatPresent){
        case INIT :
            delay_ms(100);
            break;
        case COULOIR :
            actionCouloir();
            break;
        case COUPURE :
            actionCoupure();
            break;
        case BOUCLE :
            actionBoucle();
            break;
        case MUR :
            actionMur();
            break;    
    }
}
*/

int main()
{
    DDRB |= (1 << PORTB4); 
    DDRB &= ~(1 << PORTB2);
    DDRD = 0xff;
    initialisationUART();

    Mur mur = Mur(75);
    mur.run();

    return 0;
}


