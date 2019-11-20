#define F_CPU 8000000UL

#include "selection.h"

volatile bool buttonEventBreadboard;
volatile bool buttonEventCard;

Selection::Selection(): 
    _etat(EtatSelection::leCouloir),
    compteurEtat(0),
    _lcd(LCM(&DDRA, &PORTA))
{
    buttonEventBreadboard = false;
    buttonEventCard = false;
    cli ();
    EIMSK |= (1 << INT0) | (1 << INT1) ;
    EICRA |= (1<<ISC11) | (1 << ISC01);
    sei ();
}

ISR(INT0_vect){
    _delay_ms(10);

    buttonEventCard = true;
    _delay_ms(2000);
}

ISR(INT1_vect){
    _delay_ms (10);

    buttonEventBreadboard = true;
}

void Selection::changeState(){
    switch(_etat){
        case(EtatSelection::leCouloir):
            _etat = EtatSelection::leMur;
            break;
        case(EtatSelection::leMur):
            _etat = EtatSelection::lesBoucles;
            break;
        case(EtatSelection::lesBoucles):
            _etat = EtatSelection::lesCoupures;
            break;
        case(EtatSelection::lesCoupures):
            _etat = EtatSelection::leCouloir;
            break;
        case(EtatSelection::Fin):               
            break;
    }
    if(buttonEventCard){
        ++compteurEtat;
        if (compteurEtat>4)
        {
            _etat = EtatSelection::Fin;
        }
    }else{
        buttonEventBreadboard = false;
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
                Boucle boucle_obj(75);
                boucle_obj.run();
            }
            break;
        case(EtatSelection::lesCoupures):
            _lcd.write("Les coupures", 0, true);
            if(buttonEventCard){
                Coupure coupure_obj(75);
                coupure_obj.run();
            }
            break;
        case(EtatSelection::Fin):
            _lcd.write("Fin", 0, true);
            break;
    }
}

void Selection::run(){
    while(_etat != EtatSelection::Fin){
        while(!buttonEventBreadboard || buttonEventCard);
        changeState();
        doAction();
    }
}