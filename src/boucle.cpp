#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "boucle.h"

Boucle::Boucle(uint8_t vitesse) : 
    _suiveurLigne(SuiveurLigne(vitesse))
{
    DDRC = 0x00; //DDRC en entree
};

void Boucle::run(){
    while(_etat != ETAT_BOUCLE::QUIT)
    {
        doAction();
        changeState();
    }
};

void Boucle::doAction(){
    switch(_etat){
        case ETAT_BOUCLE::ALLER_GROSSE_BOUCLE : 
        {
            uint8_t nIntersections = 0;
            while(nIntersections != 2){
                if((PINC & EXTREME_GAUCHE)&&(PINC & GAUCHE)&&(PINC & MILIEU)) {
                    nIntersections++;
                }
                _suiveurLigne.suivreLigne();
            }
            break;
        }
        case ETAT_BOUCLE::FAIRE_BOUCLE: 
            for(uint8_t j = 0; j <2; j++){
                while((PINC & EXTREME_GAUCHE)&&(PINC & GAUCHE)&&(PINC & MILIEU)){
                    _suiveurLigne.suivreLigne();
                }
                _suiveurLigne.tournerGauche();

                for (uint8_t i=0; i != 3; i++){
                    while(_suiveurLigne.suivreLigne());
                    _suiveurLigne.tournerGauche();
                }
            }
            break;

        case ETAT_BOUCLE::FIN_BOUCLE: 
            while(_suiveurLigne.suivreLigne());
            _suiveurLigne.tournerGauche();            
            break;
        
        case ETAT_BOUCLE::QUIT: break;
    }
};

void Boucle::changeState(){
    switch(_etat){
        case ETAT_BOUCLE::ALLER_GROSSE_BOUCLE : 
            _etat = ETAT_BOUCLE::FAIRE_BOUCLE;
            break;
        
        case ETAT_BOUCLE::FAIRE_BOUCLE:
            _etat = ETAT_BOUCLE::FIN_BOUCLE;
            break;

        case ETAT_BOUCLE::FIN_BOUCLE: 
            _etat = ETAT_BOUCLE::QUIT;            
            break;

        case ETAT_BOUCLE::QUIT: break;
    }
};
