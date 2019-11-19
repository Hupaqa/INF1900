
#include "couloir.h"
/*
void actionCouloir(){
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
*/
    Couloir::Couloir(uint8_t vitesse) :
<<<<<<< HEAD
        _suiveurLigne(vitesse),
        _suiveurCouloir(vitesse)
=======
        _suiveurLigne(SuiveurLigne(vitesse)), 
        _suiveurCouloir(SuiveurCouloir(vitesse)) 
>>>>>>> dbc510c2f5222582b184ed01fe100d0af9e4802c
    {
        DDRC = 0x00; //DDRC en entree
    };

    void Couloir::run(){
        while (_suiveurLigne.suivreLigne());

        _suiveurLigne.ajustementPWM(_suiveurLigne.getVitesse(), 0, _suiveurLigne.getVitesse(), 0);

        while (!(PINC & ((1<<GAUCHE) | (1<<MILIEU) | (1<<DROITE))))
        {
            if (PINC & (1<<EXTREME_GAUCHE)) {
                _suiveurLigne.redressementDroit();
            }   
            else if (PINC & 0b00000100){
                _suiveurLigne.redressementGauche();
            }
        }
        while (_suiveurLigne.suivreLigne());
        _suiveurLigne.tournerGauche();
    };