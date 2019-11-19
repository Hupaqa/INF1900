#define F_CPU 8000000UL

#include "selection.h"
#include "boucle.h"
#include "couloir.h"
#include "mur.h"
#include "coupure.h"

Selection::Selection(): 
    _etat(EtatSelection::leCouloir),
    buttonEventBreadboard(false),
    buttonEventCard(false)
    compteurEtat(0);
{
    _lcd = LCM(&ddr_lcd, port_lcd);
    cli ();
    EIMSK |= (1 << INT0) | (1 << INT1) ;
    EICRA |= (1<<ISC11) | (1 << ISC00) | (1 << ISC01);
    sei ();
}

ISR(INT0_vect){
    _delay_ms(10);

    buttonEventCard = true
}

ISR(INT1_vect){
    _delay_ms (10);

    buttonEventBreadboard = true;
}

void Selection::changeState(){
    switch(_etat){
        case(EtatSelection::leCouloir):
            _etat = EtatSelection::leMur;
            if(!buttonEventCard){
                buttonEventBreadboard = false;
            }
            break;
        case(EtatSelection::leMur):
            _etat = EtatSelection::lesBoucles;
            if(!buttonEventCard){
                buttonEventBreadboard = false;
            }
            break;
        case(EtatSelection::lesBoucles):
            _etat = EtatSelection::lesCoupures;
            if(!buttonEventCard){
                buttonEventBreadboard = false;
            }
            break;
        case(EtatSelection::lesCoupures):
            _etat = EtatSelection::leCouloir;
            if(!buttonEventCard){
                buttonEventBreadboard = false;
            }
            break;
    }
}

void Selection::doAction(){
    switch(_etat){
        case(EtatSelection::leCouloir):
            _lcd.write("Le couloir", 0, true);
            if(buttonEventCard){
                Couloir couloir_obj(75);
                couloir_obj.run();
            }
            break;
        case(EtatSelection::leMur):
            _lcd.write("Le mur", 0, true);
            if(buttonEventCard){
                Mur mur_obj(75);
                mur_obj.run();
            }
            break;
        case(EtatSelection::lesBoucles):
            _lcd.write("Les deux boucles", 0, true);
            if(buttonEventCard){
                Boucles boucles_obj(75);
                couloir_obj.run();
            }
            break;
        case(EtatSelection::lesCoupures):
            _lcd.write("Les coupures", 0, true);
            break;
        case()
    }
}

void Selection::run(){
    while(!buttonEvent || buttonEventCard)
    changeState();
}