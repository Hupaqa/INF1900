/*
MIT License
Copyright (c) 2019 
Jordan Lecourtois, Hugo Paquin, William Trépanier, Benjamin Theriault 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
    _afficheur->write("les coupures", 0, true);
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
                _music.start_sound(SON_AIGU);
                tournerDroit();
                _music.stop_sound();
                _isStateDone = true;
            }
            break;
        case ETAT_COUPURE::COUPURE2:
            if(!suivreLigne()){
                _music.start_sound(SON_GRAVE);
                tournerGauche();
                _music.stop_sound();
                _isStateDone = true;
            }
            break;
        case ETAT_COUPURE::COUPURE3:
            if(!suivreLigne()){
                _music.start_sound(SON_AIGU);
                tournerDroit();
                _music.stop_sound();
                _isStateDone = true;
            }
            break;
        case ETAT_COUPURE::COUPURE4:
            if(!suivreLigne()){
                _music.start_sound(SON_GRAVE);
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


