#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "coupure.h"

Coupure::Coupure(uint8_t vitesse, LCM* ecran) : 
    SuiveurLigne(vitesse),
    _etatCourant(ETAT_COUPURE::COUPURE1), 
    _etatFutur(ETAT_COUPURE::COUPURE1), 
    _afficheur(ecran),
    _music(Music()),
    _isStateDone(false),
    _isDone(false)
{
    DDRC = 0x00;
    DDRD = 0xff;
    _afficheur->write("Coupure", 0, true);
}

void Coupure::run(){
    while(!_isDone){
        doAction();
        changeState();
    }    
}

void Coupure::doAction(){
    switch (_etatCourant)
    {
        case ETAT_COUPURE::COUPURE1:
            if(!suivreLigne()){
                _music.start_sound(45);
                tournerDroit();
                _music.stop_sound();
                _isStateDone = true;
            }
            break;
        case ETAT_COUPURE::COUPURE2:
            if(!suivreLigne()){
                _music.start_sound(75);
                tournerGauche();
                _music.stop_sound();
                _isStateDone = true;
            }
            break;
        case ETAT_COUPURE::COUPURE3:
            if(!suivreLigne()){
                _music.start_sound(45);
                tournerDroit();
                _music.stop_sound();
                _isStateDone = true;
            }
            break;
        case ETAT_COUPURE::COUPURE4:
            if(!suivreLigne()){
                _music.start_sound(75);
                tournerGauche();
                _music.stop_sound();
                _isStateDone = true;
            }
            break;
        case ETAT_COUPURE::FIN:
            if(!suivreLigne()){
                tournerGauche();
                _isDone = true;
                _isStateDone = true;
            }
            break;                                                      
    }          

}

void Coupure::changeState(){
    if (_isStateDone){  
        switch (_etatCourant)
        {
            case ETAT_COUPURE::COUPURE1:
                _etatFutur = ETAT_COUPURE::COUPURE2;
                break;

            case ETAT_COUPURE::COUPURE2:
                _etatFutur = ETAT_COUPURE::COUPURE3;
                break;

            case ETAT_COUPURE::COUPURE3:
                _etatFutur = ETAT_COUPURE::COUPURE4;
                break;

            case ETAT_COUPURE::COUPURE4:
                _etatFutur = ETAT_COUPURE::FIN;
                break;

            case ETAT_COUPURE::FIN:
                break;                                                      
        } 
        _isStateDone = false;
        _etatCourant = _etatFutur;
    }
}


