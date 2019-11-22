#ifndef COULOIR_H
#define COULOIR_H

#include "suiveurLigne.h"

enum EtatCouloir
{
    ligneDebut,
    gauche, 
    droite, 
    ligneFin,
    virageFin
};

class Couloir : public SuiveurLigne 
{
    public:

        /**
         * 
         * 
         **/
        Couloir(uint8_t vitesse, LCM* ecran);
        void run();
        bool finCouloir();

        void doAction();
        void changeState();

    private:
        EtatCouloir _etat;
        LCM* _lcd;
        bool _isDone;
};

#endif